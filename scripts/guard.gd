extends RigidBody2D

enum State {
	IDLE,
	PURSUING
}

var currentState: State = State.IDLE
var playerDetected: bool = false
@export var speed = 60.0

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass


func _on_detection_range_body_entered(body: Node2D) -> void:
	if body.is_in_group("player"):
		playerDetected = true
		print("player detected")


func _on_detection_range_body_exited(body: Node2D) -> void:
	if body.is_in_group("player"):
		playerDetected = false
		print("player left detection")
