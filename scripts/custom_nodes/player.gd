class_name Player extends CharacterBody2D

enum States {
	IDLE,
	WALK,
	RUN,
	JUMP,
}

var state: States = States.IDLE
