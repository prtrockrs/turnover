extends Node

@onready var human_control: PlayerControl = $HumanControl
@onready var mouse_control: PlayerControl = $MouseControl

# array of all forms
@onready var controls: Array[PlayerControl] = [
	$HumanControl,
	$MouseControl,
]

var active_control: PlayerControl
var selected_index := 0 # human is default
var choosing_form := false

func _ready() -> void:
	active_control = controls[selected_index]

func setup(player: Player) -> void:
	for control in controls:
		control.setup(player)

func process_controls() -> void:
	if Input.is_action_just_pressed("player_transform"):
		print("Choosing form...")
		choosing_form = true
		selected_index = controls.find(active_control)
	
	if choosing_form:
		if Input.is_action_just_pressed("ui_right"):
			selected_index = (selected_index + 1) % controls.size()
			print("Select %d?" % [selected_index])
		elif Input.is_action_just_pressed("ui_left"):
			selected_index = (selected_index - 1 + controls.size()) % controls.size()
			print("Select %d?" % [selected_index])
	
		if Input.is_action_just_released("player_transform"):
			active_control = controls[selected_index]
			choosing_form = false
			print("%d selected." % [selected_index])
		return
	
	active_control.handle_input()

func _physics_process(delta: float) -> void:
	if active_control:
		active_control.handle_physics(delta)
