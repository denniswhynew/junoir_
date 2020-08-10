using UnityEngine;
using System.Collections;

public class eeeee : MonoBehaviour {
	NavMeshAgent m_agent;
	Transform m_transform;
	GameObject m_player;
	float m_movspeed = 0.5f;
	float m_rotspeed=0;
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
		RotateTo ();
	}
	void RotateTo()
	{
		Vector3 oldangle = m_transform.eulerAngles;
		m_transform.LookAt (m_player.transform);
		float target = m_transform.eulerAngles.y;

		float speed = m_rotspeed * Time.deltaTime;
		float angle = Mathf.MoveTowardsAngle (oldangle.y, target, speed);
		m_transform.eulerAngles = new Vector3 (0, angle, 0);
	}
	void moveto()
	{
		float speed = m_movspeed + Time.deltaTime;
		m_agent.Move (m_transform.TransformDirection ((new Vector3 (0, 0, speed))));
	}
}
