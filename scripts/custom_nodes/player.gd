class_name Player extends CharacterBody2D

enum States {
	IDLE,
	WALK,
	RUN,
	JUMP,
	FALL,
	CUTSCENE,
}

@onready var control_manager: Node = $ControlManager
@onready var sprite: AnimatedSprite2D = $AnimatedSprite2D

var current_state: States = States.IDLE

@export var collision_shape: Shape2D

func _ready() -> void:
	control_manager.setup(self)
	
func _physics_process(delta: float) -> void:
	# global gravity
	if not is_on_floor():
		velocity += get_gravity() * delta

	control_manager.process_controls()
	
	move_and_slide()
	
	_update_movement_state()
	
	_update_animations()

func _update_movement_state() -> void:
	if not is_on_floor():
		current_state = States.JUMP #if velocity.y < 0.0 else States.FALL
	elif absf(velocity.x) < 1.0:
		current_state = States.IDLE
	else:
		current_state = States.WALK

func _update_animations() -> void:
	# lazy sprite flipping
	if velocity.x < 0.0:
		sprite.flip_h = true
	elif velocity.x > 0.0:
		sprite.flip_h = false
	
	var active_control = control_manager.active_control
	var state_name = States.keys()[current_state].to_lower()
	if active_control == $ControlManager/HumanControl:
		sprite.play("human_%s" % state_name)
	elif active_control == $ControlManager/MouseControl:
		sprite.play("mouse_%s" % state_name)
	else:
		print("Error: unknown animation state")
