extends CharacterBody2D

enum State {
	IDLE,
	PURSUING
}

enum Direction {
	LEFT,
	RIGHT
}

@onready var left_ray: RayCast2D = $LeftRay
@onready var right_ray: RayCast2D = $RightRay
@onready var sprite: Sprite2D = $Sprite

var current_state: State = State.IDLE
var player_detected: bool = false
var patrol_direction: Direction = Direction.LEFT

@export var speed = 60.0

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	if not is_on_floor():
		velocity.y += get_gravity().y * delta
		
	if (current_state == State.IDLE):
		idle_behaviour()

func idle_behaviour():
	if (should_change_dir()):
		change_dir()
	
	var dir = -1 if (patrol_direction == Direction.LEFT) else 1

	velocity.x = dir * speed
	move_and_slide()
		
func should_change_dir() -> bool:
	return (
		patrol_direction == Direction.LEFT and
		not left_ray.is_colliding()
	) or (
		patrol_direction == Direction.RIGHT and
		not right_ray.is_colliding()
	)
	
func change_dir():
	patrol_direction = Direction.RIGHT if (patrol_direction == Direction.LEFT) else Direction.LEFT
	sprite.flip_h = patrol_direction == Direction.RIGHT

func _on_detection_range_body_entered(body: Node2D) -> void:
	if body.is_in_group("player"):
		player_detected = true
		print("player detected")


func _on_detection_range_body_exited(body: Node2D) -> void:
	if body.is_in_group("player"):
		player_detected = false
		print("player left detection")
