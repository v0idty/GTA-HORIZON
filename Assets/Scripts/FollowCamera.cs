using UnityEngine;

namespace GTAHorizon
{
    public sealed class FollowCamera : MonoBehaviour
    {
        public Transform target;
        private void LateUpdate()
        {
            if(target==null)return;
            Vector3 desired=target.position-target.forward*7f+Vector3.up*3.2f;
            transform.position=Vector3.Lerp(transform.position,desired,8f*Time.deltaTime);
            transform.LookAt(target.position+Vector3.up*1.1f);
        }
    }
}
