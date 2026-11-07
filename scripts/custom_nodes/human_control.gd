# human controls
extends PlayerControl

func handle_input(delta: float) -> void:
	# copied from tutorial site	
	#if state == States.IDLE:
		#velocity.x += input_direction_x * glide_acceleration * delta
		#velocity.x = min(velocity.x, glide_max_speed)

	pass

func handle_physics(delta: float) -> void:
	pass
