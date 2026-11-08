class_name PlayerControl extends Node

var player: Player

func setup(player: Player) -> void:
	self.player = player

func handle_input() -> void:
	pass

#unused until different forms have different physics
func handle_physics(delta: float) -> void:
	pass
