using UnityEngine;

namespace GTAHorizon
{
    public static class CityGenerator
    {
        public static void Build(Transform root)
        {
            var road = Cube("Coastal Boulevard", root, new Vector3(0,-.12f,0), new Vector3(18,.2f,180), new Color(.07f,.08f,.10f));
            Cube("West Sidewalk", root, new Vector3(-10,.02f,0), new Vector3(2,.25f,180), new Color(.42f,.43f,.42f));
            Cube("East Sidewalk", root, new Vector3(10,.02f,0), new Vector3(2,.25f,180), new Color(.42f,.43f,.42f));
            Cube("Waterfront", root, new Vector3(0,-.6f,100), new Vector3(300,.3f,100), new Color(.025f,.18f,.27f));
            for (int z=-70; z<=70; z+=20)
            {
                Cube("Road Marking", root, new Vector3(0,.005f,z), new Vector3(.22f,.02f,7), new Color(.92f,.82f,.48f));
                for (int side=-1; side<=1; side+=2)
                {
                    float x=side*Random.Range(19f,34f);
                    float h=Random.Range(12f,48f);
                    var building=Cube("Downtown Tower",root,new Vector3(x,h/2f,z+Random.Range(-7f,7f)),new Vector3(Random.Range(9f,15f),h,Random.Range(10f,17f)),new Color(Random.Range(.10f,.24f),Random.Range(.16f,.28f),Random.Range(.23f,.38f)));
                    building.transform.Rotate(0,Random.Range(-4f,4f),0);
                    for(int floor=2;floor<h-2;floor+=4)
                        Cube("Lit Window Band",root,new Vector3(x,h/2f-h/2f+floor,z-8.1f),new Vector3(5,.35f,.08f),new Color(.95f,.60f,.24f));
                }
            }
            for(int i=0;i<18;i++)
            {
                float z=-75+i*9;
                var trunk=Cube("Palm Trunk",root,new Vector3(-12,3,z),new Vector3(.5f,6,.5f),new Color(.25f,.13f,.07f));
                trunk.transform.rotation=Quaternion.Euler(0,0,Random.Range(-8f,8f));
                var crown=GameObject.CreatePrimitive(PrimitiveType.Sphere);
                crown.name="Palm Crown"; crown.transform.SetParent(root);
                crown.transform.position=new Vector3(-12,6.5f,z);
                crown.transform.localScale=new Vector3(4,1.1f,4);
                crown.GetComponent<Renderer>().material.color=new Color(.06f,.28f,.12f);
            }
            Cube("Beachfront Promenade",root,new Vector3(-2,.08f,75),new Vector3(60,.3f,4),new Color(.65f,.55f,.39f));
        }

        private static GameObject Cube(string name, Transform parent, Vector3 position, Vector3 scale, Color color)
        {
            var go=GameObject.CreatePrimitive(PrimitiveType.Cube);
            go.name=name; go.transform.SetParent(parent);
            go.transform.position=position; go.transform.localScale=scale;
            go.GetComponent<Renderer>().material.color=color;
            return go;
        }
    }
}
