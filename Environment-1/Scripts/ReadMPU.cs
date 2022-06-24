using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Uduino;

public class ReadMPU : MonoBehaviour {

    Vector3 position;
    Vector3 rotation;
    public Gun gun;
    public Vector3 rotationOffset ;
    public float speedFactor = 15.0f;
    public string imuName = "r"; // You should ignore this if there is one IMU.
    public Camera cam;
    void Start () {
      UduinoManager.Instance.OnDataReceived += ReadIMU;
      //  Note that here, we don't use the delegate but the Events, assigned in the Inpsector Panel
    }

    void Update() { }

    public void ReadIMU (string data, UduinoDevice device) {
        //Debug.Log(data);
        string[] values = data.Split(',');
        if (values.Length == 5 && values[0] == imuName) // Rotation of the first one 
        {
            float w = float.Parse(values[1]);
            float x = float.Parse(values[2]);
            float y = float.Parse(values[3]);
            float z = float.Parse(values[4]);
            cam.transform.localRotation = Quaternion.Lerp(cam.transform.localRotation,  new Quaternion(w, y, x, z), Time.deltaTime * speedFactor);
        } else if (values.Length ==1)
        {
              gun.Shoot();
      
        }
        else{
            Debug.LogWarning(data);
        }
        //cam.transform.parent.transform.eulerAngles = rotationOffset;
      //  Log.Debug("The new rotation is : " + transform.Find("IMU_Object").eulerAngles);
    }
}
