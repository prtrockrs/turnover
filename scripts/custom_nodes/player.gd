class_name Player extends CharacterBody2D

enum States {
	IDLE,
	WALK,
	RUN,
	JUMP,
	FALL,
	CUTSCENE,
}

var current_state: States = States.IDLE

@onready var control_manager: Node = $ControlManager

func _ready() -> void:
	control_manager.setup(self)
	
func _physics_process(delta: float) -> void:
	# global gravity
	if not is_on_floor():
		velocity += get_gravity() * delta

	control_manager.process_controls()
	
	move_and_slide()
	
	_update_animations()
	
func _update_animations() -> void:
	# Add animation player script
	#match current_state:
		#States.IDLE:
			#animation_player.play("idle")
		#States.WALK:
			#animation_player.play("walk")
		#States.RUN:
			#animation_player.play("run")
		#States.JUMP:
			#animation_player.play("jump")
		#States.FALL:
			#animation_player.play("fall")
	pass
