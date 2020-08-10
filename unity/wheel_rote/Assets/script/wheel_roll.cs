using UnityEngine;
using System.Collections;

public class wheel_roll : MonoBehaviour {
	float wheelangle;
	//bool wheelbehald;
	public bool turnRL;
	public Vector3 wheelpos;
	public Vector3 A,B;
	public Transform wheel;
	public Vector3 newM;
	public Vector3 oldM;

	public float N;
	public float mouseM;
	public Light LT;
	public Light LT1;
	// Use this for initialization
	void Start () {
		wheelangle = transform.rotation.y;
		//wheelbehald = false;
		wheelpos = transform.position;
		newM = Input.mousePosition;
		LT.intensity = 4;
		LT1.intensity = 4;
	}
	
	// Update is called once per frame
	void Update () {



		if (Input.GetMouseButton(0)) {
			RaycastHit hit;
			Ray ray;
			ray=Camera.main.ScreenPointToRay(Input.mousePosition);
			oldM = newM;
			if(Physics.Raycast(ray ,out hit))
			{
				newM = hit.point;
			}
			/*oldM = newM;
			newM = Input.mousePosition; */
			newM.z = 0;
			A.x = (wheelpos.x - oldM.x)/400;
			A.y = (wheelpos.y - oldM.y)/400;	
			A.z = 0;
			B.x = oldM.x - newM.x;
			B.y = oldM.y - newM.y;
			B.z = 0;
			mouseM = Vector3.Distance(oldM,newM);
			cross();
			if(!turnRL)
				mouseM=Mathf.Abs(mouseM)*-1;
			else
				mouseM = Mathf.Abs(mouseM);
			wheel.transform.Rotate(0,0,57*Mathf.Atan(mouseM));
			if(mouseM>0){
				LT.intensity+=0.03f;
				LT1.intensity+=0.03f;}
			else if(mouseM<0){
				LT.intensity-=0.03f;
				LT1.intensity-=0.03f;}
		}
	}

	void cross(){

		N = A.x * B.y - A.y * B.x;
		if (N > 0) {
			turnRL = true;
		} else
			turnRL = false;
	}
}
