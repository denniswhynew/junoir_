using UnityEngine;
using System.Collections;

public class av : MonoBehaviour {

	void OnTriggerEnter(Collider other)
	{
		if (other.tag.CompareTo ("self") != 0)
						return;
		Destroy(this.gameObject);
	}
}
