#ifndef _TRANSFORM_DATATYPES_H_
#define _TRANSFORM_DATATYPES_H_

#include <string>
#include <DataSet/DataType/PointStamped.h>
#include <DataSet/DataType/Vector3Stamped.h>
#include <DataSet/DataType/QuaternionStamped.h>
#include <DataSet/DataType/TransformStamped.h>
#include <DataSet/DataType/PoseStamped.h>
#include <Time/Time.h>

#include <Console/Console.h>

#include "LinearMath/Vector3.h"
#include "LinearMath/Transform.h"

namespace NS_Transform
{
  
  typedef NS_Transform::Vector3 Point;
  typedef NS_Transform::Transform Pose;
  
  static const double QUATERNION_TOLERANCE = 0.1f;
  
  /** \brief The data type which will be cross compatable with geometry_msgs
   * This is the tf datatype equivilant of a MessageStamped */
  template<typename T>
    class Stamped: public T
    {
    public:
      NS_NaviCommon::Time stamp_; ///< The timestamp associated with this data
      std::string frame_id_; ///< The frame_id associated this data
      
      /** Default constructor */
      Stamped ()
          : frame_id_ ("NO_ID_STAMPED_DEFAULT_CONSTRUCTION")
      {
      }
      ; //Default constructor used only for preallocation
      
      /** Full constructor */
      Stamped (const T& input, const NS_NaviCommon::Time& timestamp,
               const std::string & frame_id)
          : T (input), stamp_ (timestamp), frame_id_ (frame_id)
      {
      }
      ;

      /** Set the data element */
      void
      setData (const T& input)
      {
        *static_cast<T*> (this) = input;
      }
      ;
    };
  
  /** \brief Comparison Operator for Stamped datatypes */
  template<typename T>
    bool
    operator== (const Stamped<T> &a, const Stamped<T> &b)
    {
      return a.frame_id_ == b.frame_id_ && a.stamp_ == b.stamp_
          && static_cast<const T&> (a) == static_cast<const T&> (b);
    }
  ;
  
  /** \brief The Stamped Transform datatype used by tf */
  class StampedTransform: public NS_Transform::Transform
  {
  public:
    NS_NaviCommon::Time stamp_; ///< The timestamp associated with this transform
    std::string frame_id_; ///< The frame_id of the coordinate frame  in which this transform is defined
    std::string child_frame_id_; ///< The frame_id of the coordinate frame this transform defines
    StampedTransform (const NS_Transform::Transform& input,
                      const NS_NaviCommon::Time& timestamp,
                      const std::string & frame_id,
                      const std::string & child_frame_id)
        : NS_Transform::Transform (input), stamp_ (timestamp),
            frame_id_ (frame_id), child_frame_id_ (child_frame_id)
    {
    }
    ;

    /** \brief Default constructor only to be used for preallocation */
    StampedTransform ()
    {
    }
    ;

    /** \brief Set the inherited Traonsform data */
    void
    setData (const NS_Transform::Transform& input)
    {
      *static_cast<NS_Transform::Transform*> (this) = input;
    }
    ;
    
  };
  
  /** \brief Comparison operator for StampedTransform */
  static inline bool
  operator== (const StampedTransform &a, const StampedTransform &b)
  {
    return a.frame_id_ == b.frame_id_ && a.child_frame_id_ == b.child_frame_id_
        && a.stamp_ == b.stamp_
        && static_cast<const NS_Transform::Transform&> (a)
            == static_cast<const NS_Transform::Transform&> (b);
  }
  ;
  
  /** \brief convert Quaternion msg to Quaternion */
  static inline void
  quaternionMsgToTF (const NS_DataType::Quaternion& msg, Quaternion& bt)
  {
    bt = Quaternion (msg.x, msg.y, msg.z, msg.w);
    if (fabs (bt.length2 () - 1) > QUATERNION_TOLERANCE)
    {
      printf ("MSG to TF: Quaternion Not Properly Normalized");
      bt.normalize ();
    }
  }
  ;
  /** \brief convert Quaternion to Quaternion msg*/
  static inline void
  quaternionTFToMsg (const Quaternion& bt, NS_DataType::Quaternion& msg)
  {
    if (fabs (bt.length2 () - 1) > QUATERNION_TOLERANCE)
    {
      printf ("TF to MSG: Quaternion Not Properly Normalized");
      Quaternion bt_temp = bt;
      bt_temp.normalize ();
      msg.x = bt_temp.x ();
      msg.y = bt_temp.y ();
      msg.z = bt_temp.z ();
      msg.w = bt_temp.w ();
    }
    else
    {
      msg.x = bt.x ();
      msg.y = bt.y ();
      msg.z = bt.z ();
      msg.w = bt.w ();
    }
  }
  ;
  
  /** \brief Helper function for getting yaw from a Quaternion */
  static inline double
  getYaw (const Quaternion& bt_q)
  {
    tfScalar useless_pitch, useless_roll, yaw;
    NS_Transform::Matrix3x3 (bt_q).getRPY (useless_roll, useless_pitch, yaw);
    return yaw;
  }
  
  /** \brief Helper function for getting yaw from a Quaternion message*/
  static inline double
  getYaw (const NS_DataType::Quaternion& msg_q)
  {
    Quaternion bt_q;
    quaternionMsgToTF (msg_q, bt_q);
    return getYaw (bt_q);
  }
  
  /** \brief construct a Quaternion from Fixed angles
   * \param roll The roll about the X axis
   * \param pitch The pitch about the Y axis
   * \param yaw The yaw about the Z axis
   * \return The quaternion constructed
   */
  static inline NS_Transform::Quaternion
  createQuaternionFromRPY (double roll, double pitch, double yaw)
  {
    Quaternion q;
    q.setRPY (roll, pitch, yaw);
    return q;
  }
  
  /** \brief construct a Quaternion from yaw only
   * \param yaw The yaw about the Z axis
   * \return The quaternion constructed
   */
  static inline Quaternion
  createQuaternionFromYaw (double yaw)
  {
    Quaternion q;
    q.setRPY (0.0, 0.0, yaw);
    return q;
  }
  
  /** \brief construct a Quaternion Message from yaw only
   * \param yaw The yaw about the Z axis
   * \return The quaternion constructed
   */
  static inline NS_DataType::Quaternion
  createQuaternionMsgFromYaw (double yaw)
  {
    Quaternion q;
    q.setRPY (0.0, 0.0, yaw);
    NS_DataType::Quaternion q_msg;
    quaternionTFToMsg (q, q_msg);
    return q_msg;
  }
  
  /** \brief construct a Quaternion Message from Fixed angles
   * \param roll The roll about the X axis
   * \param pitch The pitch about the Y axis
   * \param yaw The yaw about the Z axis
   * \return The quaternion constructed
   */
  static inline NS_DataType::Quaternion
  createQuaternionMsgFromRollPitchYaw (double roll, double pitch, double yaw)
  {
    NS_DataType::Quaternion q_msg;
    quaternionTFToMsg (createQuaternionFromRPY (roll, pitch, yaw), q_msg);
    return q_msg;
  }
  
  /** \brief construct an Identity Quaternion
   * \return The quaternion constructed
   */
  static inline NS_Transform::Quaternion
  createIdentityQuaternion ()
  {
    Quaternion q;
    q.setRPY (0, 0, 0);
    return q;
  }
  ;
  
  /** \brief convert QuaternionStamped msg to Stamped<Quaternion> */
  static inline void
  quaternionStampedMsgToTF (const NS_DataType::QuaternionStamped & msg,
                            Stamped<Quaternion>& bt)
  {
    quaternionMsgToTF (msg.quaternion, bt);
    bt.stamp_ = msg.header.stamp;
    bt.frame_id_ = msg.header.frame_id;
  }
  ;
  /** \brief convert Stamped<Quaternion> to QuaternionStamped msg*/
  static inline void
  quaternionStampedTFToMsg (const Stamped<Quaternion>& bt,
                            NS_DataType::QuaternionStamped & msg)
  {
    quaternionTFToMsg (bt, msg.quaternion);
    msg.header.stamp = bt.stamp_;
    msg.header.frame_id = bt.frame_id_;
  }
  ;
  
  /** \brief convert Vector3 msg to Vector3 */
  static inline void
  vector3MsgToTF (const NS_DataType::Vector3& msg_v, Vector3& bt_v)
  {
    bt_v = Vector3 (msg_v.x, msg_v.y, msg_v.z);
  }
  ;
  /** \brief convert Vector3 to Vector3 msg*/
  static inline void
  vector3TFToMsg (const Vector3& bt_v, NS_DataType::Vector3& msg_v)
  {
    msg_v.x = bt_v.x ();
    msg_v.y = bt_v.y ();
    msg_v.z = bt_v.z ();
  }
  ;
  
  /** \brief convert Vector3Stamped msg to Stamped<Vector3> */
  static inline void
  vector3StampedMsgToTF (const NS_DataType::Vector3Stamped & msg,
                         Stamped<Vector3>& bt)
  {
    vector3MsgToTF (msg.vector, bt);
    bt.stamp_ = msg.header.stamp;
    bt.frame_id_ = msg.header.frame_id;
  }
  ;
  /** \brief convert Stamped<Vector3> to Vector3Stamped msg*/
  static inline void
  vector3StampedTFToMsg (const Stamped<Vector3>& bt,
                         NS_DataType::Vector3Stamped & msg)
  {
    vector3TFToMsg (bt, msg.vector);
    msg.header.stamp = bt.stamp_;
    msg.header.frame_id = bt.frame_id_;
  }
  ;
  
  /** \brief convert Point msg to Point */
  static inline void
  pointMsgToTF (const NS_DataType::Point& msg_v, Point& bt_v)
  {
    bt_v = Vector3 (msg_v.x, msg_v.y, msg_v.z);
  }
  ;
  /** \brief convert Point to Point msg*/
  static inline void
  pointTFToMsg (const Point& bt_v, NS_DataType::Point& msg_v)
  {
    msg_v.x = bt_v.x ();
    msg_v.y = bt_v.y ();
    msg_v.z = bt_v.z ();
  }
  ;
  
  /** \brief convert PointStamped msg to Stamped<Point> */
  static inline void
  pointStampedMsgToTF (const NS_DataType::PointStamped & msg,
                       Stamped<Point>& bt)
  {
    pointMsgToTF (msg.point, bt);
    bt.stamp_ = msg.header.stamp;
    bt.frame_id_ = msg.header.frame_id;
  }
  ;
  /** \brief convert Stamped<Point> to PointStamped msg*/
  static inline void
  pointStampedTFToMsg (const Stamped<Point>& bt,
                       NS_DataType::PointStamped & msg)
  {
    pointTFToMsg (bt, msg.point);
    msg.header.stamp = bt.stamp_;
    msg.header.frame_id = bt.frame_id_;
  }
  ;
  
  /** \brief convert Transform msg to Transform */
  static inline void
  transformMsgToTF (const NS_DataType::Transform& msg, Transform& bt)
  {
    bt = Transform (
        Quaternion (msg.rotation.x, msg.rotation.y, msg.rotation.z,
                    msg.rotation.w),
        Vector3 (msg.translation.x, msg.translation.y, msg.translation.z));
  }
  ;
  /** \brief convert Transform to Transform msg*/
  static inline void
  transformTFToMsg (const Transform& bt, NS_DataType::Transform& msg)
  {
    vector3TFToMsg (bt.getOrigin (), msg.translation);
    quaternionTFToMsg (bt.getRotation (), msg.rotation);
  }
  ;
  
  /** \brief convert TransformStamped msg to NS_Transform::StampedTransform */
  static inline void
  transformStampedMsgToTF (const NS_DataType::TransformStamped & msg,
                           StampedTransform& bt)
  {
    transformMsgToTF (msg.transform, bt);
    bt.stamp_ = msg.header.stamp;
    bt.frame_id_ = msg.header.frame_id;
    bt.child_frame_id_ = msg.child_frame_id;
  }
  ;
  /** \brief convert NS_Transform::StampedTransform to TransformStamped msg*/
  static inline void
  transformStampedTFToMsg (const StampedTransform& bt,
                           NS_DataType::TransformStamped & msg)
  {
    transformTFToMsg (bt, msg.transform);
    msg.header.stamp = bt.stamp_;
    msg.header.frame_id = bt.frame_id_;
    msg.child_frame_id = bt.child_frame_id_;
  }
  ;
  
  /** \brief convert Pose msg to Pose */
  static inline void
  poseMsgToTF (const NS_DataType::Pose& msg, Pose& bt)
  {
    bt = Transform (
        Quaternion (msg.orientation.x, msg.orientation.y, msg.orientation.z,
                    msg.orientation.w),
        Vector3 (msg.position.x, msg.position.y, msg.position.z));
  }
  ;
  /** \brief convert Pose to Pose msg*/
  static inline void
  poseTFToMsg (const Pose& bt, NS_DataType::Pose& msg)
  {
    pointTFToMsg (bt.getOrigin (), msg.position);
    quaternionTFToMsg (bt.getRotation (), msg.orientation);
  }
  ;
  
  /** \brief convert PoseStamped msg to Stamped<Pose> */
  static inline void
  poseStampedMsgToTF (const NS_DataType::PoseStamped & msg, Stamped<Pose>& bt)
  {
    poseMsgToTF (msg.pose, bt);
    bt.stamp_ = msg.header.stamp;
    bt.frame_id_ = msg.header.frame_id;
  }
  ;
  /** \brief convert Stamped<Pose> to PoseStamped msg*/
  static inline void
  poseStampedTFToMsg (const Stamped<Pose>& bt, NS_DataType::PoseStamped & msg)
  {
    poseTFToMsg (bt, msg.pose);
    msg.header.stamp = bt.stamp_;
    msg.header.frame_id = bt.frame_id_;
  }
  ;

}
#endif //TF_TRANSFORM_DATATYPES_H
