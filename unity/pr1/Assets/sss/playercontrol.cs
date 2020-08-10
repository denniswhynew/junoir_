using UnityEngine;
using System.Collections;

public class playercontrol : MonoBehaviour {

	// Use this for initialization
	public int mylife = 10;

	void Start () {

	}
	
	// Update is called once per frame
	void Update () {
		//OnTriggerEnter ();
		mylife = 10;
	}
	void OnTriggerEnter(Collider cc)
	{
		if(cc.tag.CompareTo("Enemy") != 0)
		{
			mylife -= 1;
			if(mylife <=0)
			{
				Destroy(this.gameObject);
			}
		}
	}
}
