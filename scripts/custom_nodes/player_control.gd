class_name PlayerControl extends Node

var character: Player

func handle_input(delta: float) -> void:
	#temporary example; match is switch case
	match character.current_state:
		character.States.IDLE:
			var direction = Input.get_vector("ui_left", "ui_right", "ui_up", "ui_down")
			character.velocity.x = direction.x * 300.0
	pass

func handle_physics(delta: float) -> void:
	pass
