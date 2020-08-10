using UnityEngine;
using System.Collections;

public class va : MonoBehaviour {
	//float cc = 0.5f;
	void Update()
	{
		//gameObject.transform.position += new Vector3 (0, -cc * Time.deltaTime, 0);
	}

	void OnTriggerEnter(Collider other)
	{
		if ((other.tag.CompareTo ("Enemy")) != 0)
		{Destroy(this.gameObject);
		 
		}
	}
}
