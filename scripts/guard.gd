extends CharacterBody2D

enum State {
	IDLE,
	PURSUING,
	CAPTURING,
	CAPTURED,
}

enum Direction {
	LEFT,
	RIGHT
}

const CAPTURE_DISTANCE: float = 60.0
const PATROL_SPEED: float = 50.0
const PURSUING_SPEED: float = 100.0

@onready var left_ray: RayCast2D = $LeftRay
@onready var right_ray: RayCast2D = $RightRay
@onready var sprite: Sprite2D = $Sprite

var current_state: State = State.IDLE
var direction: Direction = Direction.LEFT
var player: CharacterBody2D = null

@export var speed = PATROL_SPEED

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _physics_process(delta: float) -> void:
	if not is_on_floor():
		velocity.y += get_gravity().y * delta
		
	transition_states_if_needed()
		
	if (current_state == State.IDLE):
		idle_behaviour()
	elif (current_state == State.PURSUING):
		pursuing_behaviour()
	elif (current_state == State.CAPTURING):
		capturing_behaviour()
		
	move_and_slide()
		
func transition_states_if_needed():
	if current_state == State.IDLE and player != null:
		current_state = State.PURSUING
	elif current_state == State.PURSUING and player != null:
		if player_in_capture_range():
			print("capturing player")
			current_state = State.CAPTURING
	elif current_state == State.PURSUING and player == null:
		current_state = State.IDLE
			
# to lock the guard in a capture animation
# so the player isnt like, immediately killed game over
func capturing_behaviour() -> void:
	velocity.x = 0

# chases player to the limits of the platform placed on
# moves at an increased speed towards player
# as long as it doesnt cause it to fall off ledge
func pursuing_behaviour() -> void:	
	set_direction(dir_to_player())
	
	if direction == Direction.LEFT and left_ray.is_colliding():
		velocity.x = -PURSUING_SPEED
	elif direction == Direction.RIGHT and right_ray.is_colliding():
		velocity.x = PURSUING_SPEED
	else:
		velocity.x = 0
		
# currently just patrols the platform the guard is placed on
# expand for more movement when more platforms developed
func idle_behaviour() -> void:
	if (should_reverse_dir()):
		var new_direction = Direction.RIGHT if direction == Direction.LEFT else Direction.LEFT
		set_direction(new_direction)
	
	var dir = -1 if (direction == Direction.LEFT) else 1

	velocity.x = dir * speed
	
# requires that player != null
func player_in_capture_range() -> bool:
	return (global_position.distance_to(player.global_position) <= CAPTURE_DISTANCE)

func dir_to_player() -> Direction:
	var dir = sign(player.global_position.x - global_position.x)
	return Direction.LEFT if dir < 0 else Direction.RIGHT
		
func should_reverse_dir() -> bool:
	return (
		direction == Direction.LEFT and
		not left_ray.is_colliding()
	) or (
		direction == Direction.RIGHT and
		not right_ray.is_colliding()
	)
	
func set_direction(new_direction: Direction) -> void:
	direction = new_direction
	sprite.flip_h = direction == Direction.RIGHT

func _on_detection_range_body_entered(body: Node2D) -> void:
	if body.is_in_group("player"):
		player = body
		print("player detected")

func _on_detection_range_body_exited(body: Node2D) -> void:
	if body == player:
		player = null
		print("player left detection")
