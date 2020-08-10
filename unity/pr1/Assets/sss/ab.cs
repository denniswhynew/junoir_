using UnityEngine;
using System.Collections;

public class ab : MonoBehaviour {

	public float m_speed = 10;
	public float m_liveTime = 5;

	protected Transform m_transform;

	// Use this for initialization
	void Start () {
		m_transform = this.transform;
	}
	
	// Update is called once per frame
	void Update () {
		m_liveTime -= Time.deltaTime;

		if (m_liveTime <= 0)
			Destroy (this.gameObject);

		m_transform.Translate(new Vector3 (0, 0, -m_speed * Time.deltaTime));

	}
}
