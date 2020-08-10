using UnityEngine;
using System.Collections;

public class enimy : MonoBehaviour {
	NavMeshAgent m_agent;
	Transform m_transform;
	GameObject m_player;
	float m_movspeed = 0.5f;
	// Use this for initialization
	void Start () {
		m_transform = this.transform;
		m_player = GameObject.FindGameObjectWithTag("Player");
		m_agent = GetComponent<NavMeshAgent> ();
		m_agent.SetDestination (m_player.transform.position);
	}
	
	// Update is called once per frame
	void Update () {
		moveto ();
		//OnTriggerEnter ();
	}
	void moveto()
	{
		float speed = m_movspeed + Time.deltaTime;
		m_agent.Move (m_transform.TransformDirection ((new Vector3 (0, 0, speed))));
	}
	void OnTriggerEnter(Collider collid)
	{
		if(collid.tag.CompareTo("Rocket") != 0)
		{
			Destroy(this.gameObject);
		}
		else if(collid.tag.CompareTo("self") != 0)
		{
			Destroy(this.gameObject);
		}
	}

}
