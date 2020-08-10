using UnityEngine;
using System.Collections;

public class justtest : MonoBehaviour {

	public GameObject fireball;
	public float distance;
	public Transform firepos;
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		//OnTriggerEnter ();
		if(Input.GetMouseButtonDown(0))
		{
			RaycastHit hit;
			Vector3 point;
			if(Physics.Raycast(Camera.main.transform.position, Camera.main.transform.forward, out hit))
			{
				point = hit.point;
			}else
			{
				point = Camera.main.transform.position + Camera.main.transform.forward * distance;
			}

			GameObject go;
			go = Instantiate(fireball, firepos.transform.position , this.transform.rotation )as GameObject;
			go.transform.LookAt(point);
			go.GetComponent<Rigidbody>().AddForce(go.transform.forward * -1000.0f);

			Destroy(go,10);
		}
	}
	void OnTriggerEnter(Collider other)
	{
		if(other.tag.CompareTo("Enemy") != 0)
		{
			Destroy(this.gameObject);
		}
	}
}
