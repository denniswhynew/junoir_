using UnityEngine;
using System.Collections;

public class eeee : MonoBehaviour {
	
	// Use this for initialization
	void Start () {

	}
	float speed = 30f;
	// Update is called once per frame
	void Update () {
		//OnTriggerEnter ();
		if (gameObject.transform.position.z != 0) {
			if(gameObject.transform.position.z > 0)
				gameObject.transform.position+=new Vector3(0,0,-speed*Time.deltaTime);
			else
				gameObject.transform.position+=new Vector3(0,0,+speed*Time.deltaTime);
		}
		if (gameObject.transform.position.x != 0) {
			if(gameObject.transform.position.x > 0)
				gameObject.transform.position+=new Vector3(-speed*Time.deltaTime,0,0);
			else
				gameObject.transform.position+=new Vector3(+speed*Time.deltaTime,0,0);
		}
		if (gameObject.transform.position.y != 50) {
			if(gameObject.transform.position.y > 50)
				gameObject.transform.position+=new Vector3(0,(-speed/6)*Time.deltaTime,0);
			else
				gameObject.transform.position+=new Vector3(0,(+speed/6)*Time.deltaTime,0);
		}
	}
	void OnTriggerEnter(Collider other)
	{
		if(other.tag.CompareTo("Rocket") != 0)
		{
			Destroy(this.gameObject);
		}
		else if(other.tag.CompareTo("self") != 0)
		{
			Destroy(this.gameObject);
		}
	}

}
