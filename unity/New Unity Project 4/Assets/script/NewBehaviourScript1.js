#pragma strict

var I : Vector3;
var II : GameObject;
var T : Vector3;
var N : float;
var III : Vector3;

function Start () {
	I = this.transform.position;
}

function Update () {
	if(this.transform.position.y - I.y > 0)
	{
		N = this.transform.position.y - I.y;
		I.y = this.transform.position.y;
		II.transform.position.y -= N;
	}
	else
	{
		N = this.transform.position.y - I.y;
		I.y = this.transform.position.y;
		II.transform.position.y -= N;
	}
}