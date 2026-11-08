extends PlayerControl

const SPEED = 600.0
const JUMP_VELOCITY = -600.0

func handle_input() -> void:
	if Input.is_action_just_pressed("player_jump") and player.is_on_floor():
		player.velocity.y = JUMP_VELOCITY
		
	var direction := Input.get_axis("player_left", "player_right")

	if direction != 0.0:
		player.velocity.x = direction * SPEED
	else:
		player.velocity.x = move_toward(player.velocity.x, 0.0, SPEED)

func handle_physics(delta: float) -> void:
	pass
