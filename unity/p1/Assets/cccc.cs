using UnityEngine;
using System.Collections;

public class cccc : MonoBehaviour {
	
	// Use this for initialization
	public float speed;
	public float CD;
	public float timer;
	public float Firespeed;
	public GameObject BBB;
	public Transform TR1;
	public Transform TR2;
	public int AB;
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
		CD = 1 / (Firespeed / 100);
		
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
			if(AB==1){
				AB=2;
				Instantiate(BBB,TR1.transform.position,TR1.transform.rotation);
			}else{
				if(AB==2){
					AB=1;
					Instantiate(BBB,TR2.transform.position,TR2.transform.rotation);
				}
			}
		}else
		{
			timer =timer+Time.deltaTime;
		}
	}
}
