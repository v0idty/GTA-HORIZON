using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.UI;

namespace GTAHorizon
{
    public static class HUD
    {
        private static PlayerMotor player;
        public static void Create(PlayerMotor target)
        {
            player=target;
            RuntimeBootstrap.EnsureEventSystem();
            var root=new GameObject("Horizon HUD");
            var canvas=root.AddComponent<Canvas>(); canvas.renderMode=RenderMode.ScreenSpaceOverlay;
            var scaler=root.AddComponent<CanvasScaler>(); scaler.uiScaleMode=CanvasScaler.ScaleMode.ScaleWithScreenSize; scaler.referenceResolution=new Vector2(1920,1080);
            root.AddComponent<GraphicRaycaster>();
            var label=RuntimeBootstrap.UILabel("HORIZON CITY  /  FREE ROAM",root.transform,24,FontStyle.Bold,Color.white);
            label.rectTransform.anchorMin=new Vector2(.03f,.92f); label.rectTransform.anchorMax=new Vector2(.55f,.99f); label.rectTransform.offsetMin=label.rectTransform.offsetMax=Vector2.zero;
            var action=RuntimeBootstrap.UIButton("ACTION",root.transform,new Vector2(.88f,.18f),new Vector2(210,90));
            action.onClick.AddListener(player.ToggleVehicle);
            MakeMoveButton(root.transform,"▲",new Vector2(.12f,.20f),new Vector2(0,1));
            MakeMoveButton(root.transform,"▼",new Vector2(.12f,.08f),new Vector2(0,-1));
            MakeMoveButton(root.transform,"◀",new Vector2(.05f,.14f),new Vector2(-1,0));
            MakeMoveButton(root.transform,"▶",new Vector2(.19f,.14f),new Vector2(1,0));
        }
        private static void MakeMoveButton(Transform parent,string text,Vector2 anchor,Vector2 direction)
        {
            var b=RuntimeBootstrap.UIButton(text,parent,anchor,new Vector2(105,105));
            var hold=b.gameObject.AddComponent<MoveHold>(); hold.direction=direction;
        }
        public static void Refresh(PlayerMotor p){}
    }

    public sealed class MoveHold : MonoBehaviour, IPointerDownHandler, IPointerUpHandler, IPointerExitHandler
    {
        public Vector2 direction;
        public void OnPointerDown(PointerEventData e){ if(HUDPlayer!=null) HUDPlayer.SetTouch(direction); }
        public void OnPointerUp(PointerEventData e){ if(HUDPlayer!=null) HUDPlayer.SetTouch(Vector2.zero); }
        public void OnPointerExit(PointerEventData e){ if(HUDPlayer!=null) HUDPlayer.SetTouch(Vector2.zero); }
        private PlayerMotor HUDPlayer => FindObjectOfType<PlayerMotor>();
    }
}
