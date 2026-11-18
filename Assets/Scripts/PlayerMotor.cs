using UnityEngine;

namespace GTAHorizon
{
    [RequireComponent(typeof(CharacterController))]
    public sealed class PlayerMotor : MonoBehaviour
    {
        private CharacterController controller;
        private Transform car;
        private bool driving;
        private float vertical;
        private Vector2 touchMove;
        public bool IsDriving => driving;

        public void Setup(Transform world)
        {
            controller=gameObject.AddComponent<CharacterController>();
            controller.height=1.8f; controller.radius=.35f;
            var body=GameObject.CreatePrimitive(PrimitiveType.Capsule);
            body.name="Player Visual"; body.transform.SetParent(transform);
            body.transform.localPosition=Vector3.zero; body.transform.localScale=new Vector3(.75f,1f,.75f);
            body.GetComponent<Renderer>().material.color=new Color(.12f,.55f,.8f);
            var vehicle=GameObject.CreatePrimitive(PrimitiveType.Cube);
            vehicle.name="Horizon Sports Coupe"; vehicle.transform.SetParent(world);
            vehicle.transform.position=new Vector3(3,.8f,2);
            vehicle.transform.localScale=new Vector3(2.1f,.8f,4.1f);
            vehicle.GetComponent<Renderer>().material.color=new Color(.035f,.045f,.065f);
            car=vehicle.transform;
            foreach(var offset in new[]{new Vector3(-.9f,-.25f,1.2f),new Vector3(.9f,-.25f,1.2f),new Vector3(-.9f,-.25f,-1.2f),new Vector3(.9f,-.25f,-1.2f)})
            {
                var wheel=GameObject.CreatePrimitive(PrimitiveType.Cylinder);
                wheel.transform.SetParent(car); wheel.transform.localPosition=offset;
                wheel.transform.localRotation=Quaternion.Euler(0,0,90);
                wheel.transform.localScale=new Vector3(.42f,.18f,.42f);
                wheel.GetComponent<Renderer>().material.color=Color.black;
            }
        }

        private void Update()
        {
            if(controller==null) return;
            if(Input.GetKeyDown(KeyCode.E)) ToggleVehicle();
            Vector2 input=new Vector2(Input.GetAxisRaw("Horizontal"),Input.GetAxisRaw("Vertical"))+touchMove;
            input=Vector2.ClampMagnitude(input,1);
            if(driving)
            {
                float speed=Input.GetKey(KeyCode.Space)?5f:12f;
                car.Translate(Vector3.forward*input.y*speed*Time.deltaTime,Space.Self);
                car.Rotate(Vector3.up,input.x*75f*Time.deltaTime);
                transform.position=car.position+car.right*1.8f;
            }
            else
            {
                Vector3 move=(transform.forward*input.y+transform.right*input.x)*5.5f;
                if(controller.isGrounded) vertical=-1f;
                vertical+=Physics.gravity.y*Time.deltaTime;
                controller.Move((move+Vector3.up*vertical)*Time.deltaTime);
                if(move.sqrMagnitude>.01f) transform.rotation=Quaternion.Slerp(transform.rotation,Quaternion.LookRotation(move),12f*Time.deltaTime);
            }
        }

        public void SetTouch(Vector2 value){touchMove=value;}
        public void ToggleVehicle()
        {
            if(car==null) return;
            if(!driving && Vector3.Distance(transform.position,car.position)<5f)
            { driving=true; transform.position=car.position; }
            else if(driving)
            { driving=false; transform.position=car.position+car.right*2.2f; }
            HUD.Refresh(this);
        }
    }
}
