using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMotor : MonoBehaviour
{
    private CharacterController controller;
    private Vector3 playerVelocity;
    private bool isGrounded;
    public float gravity = -9.8f;
    public float speed = 5f;
    public float jumpHeight = 3f;
    public Camera cam;
    // Start is called before the first frame update
    void Start()
    {
        controller = GetComponent<CharacterController>();
        
    }

    // Update is called once per frame
    void Update()
    {
        isGrounded = controller.isGrounded;
        
    }

    public void ProcessMove(Vector2 input){
        //this part of the code is responsible for movement

        /* 
        Vector3 moveDirection = Vector3.zero;
        moveDirection.x = input.x;
        moveDirection.z = input.y;
        */
       Vector3 moveDirection =  (cam.transform.forward * +input.y + cam.transform.right * +input.x).normalized;
        controller.Move(transform.TransformDirection(moveDirection) * speed * Time.deltaTime);
        
        playerVelocity.y += gravity * Time.deltaTime;
        if(isGrounded && playerVelocity.y < 0){
            playerVelocity.y = -2f;
        }
        controller.Move(playerVelocity * Time.deltaTime);

    }

    public void Jump(){

        if(isGrounded){
            playerVelocity.y = Mathf.Sqrt(jumpHeight * -2.0f * gravity);
        }
    }
}
