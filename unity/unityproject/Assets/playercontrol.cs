using UnityEngine;
using System.Collections;

public class playercontrol : MonoBehaviour {
	
	// Use this for initialization
	public float speed;
	public float CD;
	public float timer;
	public float Firespeed;
	public GameObject BBB;
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
		if(Input.GetKey (KeyCode.Space))
		{
			Fire();
		}
		
		if (Input.GetKey (KeyCode.W)) {
			gameObject.transform.position+=new Vector3(-speed*Time.deltaTime,0,0);
		}
		if (Input.GetKey (KeyCode.A)) {
			gameObject.transform.position+=new Vector3(0,0,-speed*Time.deltaTime);
		}
		if (Input.GetKey (KeyCode.S)) {
			gameObject.transform.position+=new Vector3(+speed*Time.deltaTime,0,0);
		}
		if (Input.GetKey (KeyCode.D)) {
			gameObject.transform.position+=new Vector3(0,0,+speed*Time.deltaTime);
		}
	}
	
	void Fire()
	{
		if(timer>CD)
		{
			timer=0;
			Instantiate(BBB,this.transform.position,this.transform.rotation);
		}else
		{
			timer =timer+Time.deltaTime;
		}
	}
}
