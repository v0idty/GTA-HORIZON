using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.Rendering;
using UnityEngine.Rendering.Universal;

namespace GTAHorizon
{
    public sealed class RuntimeBootstrap : MonoBehaviour
    {
        private static bool started;
        private GameObject menu;
        private GameObject world;
        private PlayerMotor player;

        [RuntimeInitializeOnLoadMethod(RuntimeInitializeLoadType.AfterSceneLoad)]
        private static void StartGame()
        {
            if (started) return;
            started = true;
            new GameObject("GTA HORIZON Runtime").AddComponent<RuntimeBootstrap>();
        }

        private void Awake()
        {
            Application.targetFrameRate = 60;
            Screen.orientation = ScreenOrientation.LandscapeLeft;
            BuildLighting();
            BuildMenu();
        }

        private void BuildLighting()
        {
            RenderSettings.ambientMode = AmbientMode.Trilight;
            RenderSettings.ambientSkyColor = new Color(.24f, .34f, .48f);
            RenderSettings.ambientEquatorColor = new Color(.18f, .20f, .25f);
            RenderSettings.ambientGroundColor = new Color(.07f, .08f, .10f);
            var sun = new GameObject("Horizon Sun").AddComponent<Light>();
            sun.type = LightType.Directional;
            sun.intensity = 1.15f;
            sun.color = new Color(1f, .78f, .61f);
            sun.transform.rotation = Quaternion.Euler(42f, -32f, 0f);
            RenderSettings.sun = sun;
        }

        private void BuildMenu()
        {
            menu = new GameObject("Main Menu");
            var canvas = menu.AddComponent<Canvas>();
            canvas.renderMode = RenderMode.ScreenSpaceOverlay;
            var scaler = menu.AddComponent<UnityEngine.UI.CanvasScaler>();
            scaler.uiScaleMode = UnityEngine.UI.CanvasScaler.ScaleMode.ScaleWithScreenSize;
            scaler.referenceResolution = new Vector2(1920, 1080);
            menu.AddComponent<UnityEngine.UI.GraphicRaycaster>();
            EnsureEventSystem();

            var bg = UIBlock("Menu Backdrop", menu.transform, new Color(.025f,.055f,.12f,.98f));
            Stretch(bg.rectTransform);
            var title = UILabel("GTA HORIZON", menu.transform, 92, FontStyle.Bold, new Color(.18f,.82f,1f));
            title.rectTransform.anchorMin = new Vector2(.08f,.53f);
            title.rectTransform.anchorMax = new Vector2(.72f,.83f);
            title.rectTransform.offsetMin = title.rectTransform.offsetMax = Vector2.zero;
            var subtitle = UILabel("A CITY WITHOUT LIMITS  •  VERSION 0.1", menu.transform, 26, FontStyle.Bold, Color.white);
            subtitle.rectTransform.anchorMin = new Vector2(.10f,.46f);
            subtitle.rectTransform.anchorMax = new Vector2(.70f,.55f);
            subtitle.rectTransform.offsetMin = subtitle.rectTransform.offsetMax = Vector2.zero;
            var play = UIButton("START EXPLORING", menu.transform, new Vector2(.22f,.30f), new Vector2(420,92));
            play.onClick.AddListener(StartWorld);
            var note = UILabel("MOBILE OPEN-WORLD PROTOTYPE", menu.transform, 18, FontStyle.Normal, new Color(.72f,.82f,.92f));
            note.rectTransform.anchorMin = new Vector2(.08f,.06f);
            note.rectTransform.anchorMax = new Vector2(.65f,.13f);
            note.rectTransform.offsetMin = note.rectTransform.offsetMax = Vector2.zero;
        }

        private void StartWorld()
        {
            if (menu != null) Destroy(menu);
            world = new GameObject("Horizon City");
            CityGenerator.Build(world.transform);
            player = new GameObject("Player").AddComponent<PlayerMotor>();
            player.transform.position = new Vector3(0, 1.2f, -8);
            player.Setup(world.transform);
            var cam = new GameObject("Player Camera").AddComponent<Camera>();
            cam.tag = "MainCamera";
            cam.fieldOfView = 65;
            cam.gameObject.AddComponent<AudioListener>();
            cam.gameObject.AddComponent<FollowCamera>().target = player.transform;
            HUD.Create(player);
        }

        public static void EnsureEventSystem()
        {
            if (FindObjectOfType<EventSystem>() == null)
                new GameObject("EventSystem", typeof(EventSystem), typeof(StandaloneInputModule));
        }

        internal static UnityEngine.UI.Image UIBlock(string name, Transform parent, Color color)
        {
            var go = new GameObject(name, typeof(RectTransform), typeof(UnityEngine.UI.Image));
            go.transform.SetParent(parent, false);
            var image = go.GetComponent<UnityEngine.UI.Image>();
            image.color = color;
            return image;
        }

        internal static UnityEngine.UI.Text UILabel(string value, Transform parent, int size, FontStyle style, Color color)
        {
            var go = new GameObject("Text", typeof(RectTransform), typeof(UnityEngine.UI.Text));
            go.transform.SetParent(parent, false);
            var text = go.GetComponent<UnityEngine.UI.Text>();
            text.text = value;
            text.font = Resources.GetBuiltinResource<Font>("Arial.ttf");
            text.fontSize = size;
            text.fontStyle = style;
            text.color = color;
            text.alignment = TextAnchor.MiddleLeft;
            return text;
        }

        internal static UnityEngine.UI.Button UIButton(string label, Transform parent, Vector2 anchor, Vector2 size)
        {
            var image = UIBlock("Button " + label, parent, new Color(.02f,.48f,.72f,.95f));
            var rect = image.rectTransform;
            rect.anchorMin = rect.anchorMax = anchor;
            rect.sizeDelta = size;
            var button = image.gameObject.AddComponent<UnityEngine.UI.Button>();
            var text = UILabel(label, image.transform, 28, FontStyle.Bold, Color.white);
            Stretch(text.rectTransform);
            return button;
        }

        internal static void Stretch(RectTransform rect)
        {
            rect.anchorMin = Vector2.zero; rect.anchorMax = Vector2.one;
            rect.offsetMin = Vector2.zero; rect.offsetMax = Vector2.zero;
        }
    }
}
