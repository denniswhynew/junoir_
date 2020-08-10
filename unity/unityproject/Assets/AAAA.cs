using UnityEngine;
using System.Collections;

public class AAAA : MonoBehaviour {

	// Use this for initialization
	public GameObject Atr;
	public GameObject Btr;
	public float Rspeed;
	void Start () {
		Atr = this.gameObject;
	}
	
	// Update is called once per frame
	void Update () {
		this.transform.rotation = Atr.transform.rotation;
		Atr.transform.rotation = Quaternion.Slerp (Atr.transform.rotation, Quaternion.LookRotation (Btr.transform.position - Atr.transform.position), Rspeed * Time.deltaTime);
	}
}
