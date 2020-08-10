#pragma strict

var myTimer :float = 10.0;

function Start () {

}

function Update () {
	if(myTimer > 0){
	myTimer -= Time.deltaTime;
	guiText.text = myTimer + "";
	}else Application.LoadLevel ("sample1");
}