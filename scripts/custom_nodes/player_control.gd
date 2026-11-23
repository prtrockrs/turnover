class_name PlayerControl extends Node

var player: Player
@export var sprite: AnimatedSprite2D
@export var collision: CollisionShape2D

func setup(player: Player) -> void:
	self.player = player

func handle_input() -> void:
	pass

#unused until different forms have different physics
func handle_physics(delta: float) -> void:
	pass
