#pragma strict
var image : Texture;
function Start () {

}

function Update () {

}

function OnGUI(){
	if(GUI.Button(Rect(10,70,50,30),"Click"))
		Application.LoadLevel ("count");
}