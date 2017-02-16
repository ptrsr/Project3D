require 'GameObject'
StartPlane = GameObject:new{name = "StartPlane",x = 5.5,y = 2,z = 28, rotationX = 0.0000, rotationY = 180.0000, rotationZ = 0.0000}
JoinPlane = GameObject:new{name = "JoinPlane",x = 5.5,y = 2,z = 28, rotationX = 0.0000, rotationY = 270.0000, rotationZ = 0.0000}
CreditsPlane = GameObject:new{name = "CreditsPlane",x = 5.5,y = 2,z = 28, rotationX = 0.0000, rotationY = 90.0000, rotationZ = 0.0000}
LevelPlane = GameObject:new{name = "LevelPlane",x = 4.5,y = 8,z = -4.5, rotationX = -45.0000, rotationY = 180.0000, rotationZ = 0.0000}
Playfield = GameObject:new{name = "Playfield",mesh = "Cubes.obj",x = 4.5,y = 0,z = 4.5,r = 1,g = 1,b = 1, rotationX = 0.0000, rotationY = 0.0000, rotationZ = 0.0000}
FullArray = GameObject:new{name = "FullArray",mesh = "Cubes.obj",x = 5,y = 0,z = 30,r = 1,g = 1,b = 1, rotationX = 0.0000, rotationY = 0.0000, rotationZ = 0.0000}
temple = GameObject:new{name = "temple",mesh = "temple.obj",x = 6,y = 4,z = 44.5,r = 0.4117647,g = 0.3487889,b = 0.2361592, rotationX = 0.0000, rotationY = 180.0000, rotationZ = 0.0000}
temple1 = GameObject:new{name = "temple1",mesh = "temple.obj",x = 4.5,y = 4.5,z = 17.5,r = 0.4117647,g = 0.3487889,b = 0.2361592, rotationX = 0.0000, rotationY = 180.0000, rotationZ = 0.0000}
temple2 = GameObject:new{name = "temple2",mesh = "temple.obj",x = 18,y = 4,z = 34.5,r = 0.4117647,g = 0.3487889,b = 0.2361592, rotationX = 0.0000, rotationY = 251.9263, rotationZ = 0.0000}
rock_2 = GameObject:new{name = "rock_2",mesh = "rock_2.obj",x = 5.47,y = 0.5,z = 33.5,r = 0.3823529,g = 0.2949081,b = 0.2277249, rotationX = 0.0000, rotationY = 279.2325, rotationZ = 0.0000}
rock_21 = GameObject:new{name = "rock_21",mesh = "rock_2.obj",x = 2.47,y = 0.5,z = 31.5,r = 0.3823529,g = 0.2949081,b = 0.2277249, rotationX = 0.0000, rotationY = 0.0000, rotationZ = 0.0000}
rock_22 = GameObject:new{name = "rock_22",mesh = "rock_2.obj",x = 11.17,y = 0.77,z = 33.41,r = 0.3823529,g = 0.2949081,b = 0.2277249, rotationX = 0.0000, rotationY = 321.5475, rotationZ = 0.0000}
rock_23 = GameObject:new{name = "rock_23",mesh = "rock_2.obj",x = 1.97,y = 0.5,z = 25,r = 0.3823529,g = 0.2949081,b = 0.2277249, rotationX = 0.0000, rotationY = 305.9084, rotationZ = 0.0000}
playfield_corner = GameObject:new{name = "playfield_corner",mesh = "playfield_corner.obj",x = -0.5,y = 0,z = 9.5,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 0.0000, rotationZ = 0.0000}
playfield_corner1 = GameObject:new{name = "playfield_corner1",mesh = "playfield_corner.obj",x = -0.5,y = 0,z = -0.5,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 270.0000, rotationZ = 0.0000}
playfield_corner2 = GameObject:new{name = "playfield_corner2",mesh = "playfield_corner.obj",x = 9.5,y = 0,z = -0.5,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 180.0000, rotationZ = 0.0000}
playfield_corner3 = GameObject:new{name = "playfield_corner3",mesh = "playfield_corner.obj",x = 9.5,y = 0,z = 9.5,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 90.0000, rotationZ = 0.0000}
playfield_wall = GameObject:new{name = "playfield_wall",mesh = "playfield_wall.obj",x = -0.5,y = 0,z = 2.5,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 0.0000, rotationZ = 0.0000}
playfield_wall1 = GameObject:new{name = "playfield_wall1",mesh = "playfield_wall.obj",x = -0.5,y = 0,z = 6.5,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 0.0000, rotationZ = 0.0000}
playfield_wall2 = GameObject:new{name = "playfield_wall2",mesh = "playfield_wall.obj",x = 9.5,y = 0,z = 6.5,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 180.0000, rotationZ = 0.0000}
playfield_wall3 = GameObject:new{name = "playfield_wall3",mesh = "playfield_wall.obj",x = 9.5,y = 0,z = 2.5,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 180.0000, rotationZ = 0.0000}
playfield_wall4 = GameObject:new{name = "playfield_wall4",mesh = "playfield_wall.obj",x = 2.5,y = 0,z = 9.5,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 90.0000, rotationZ = 0.0000}
playfield_wall5 = GameObject:new{name = "playfield_wall5",mesh = "playfield_wall.obj",x = 6.5,y = 0,z = 9.5,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 90.0000, rotationZ = 0.0000}
playfield_wall6 = GameObject:new{name = "playfield_wall6",mesh = "playfield_wall.obj",x = 6.5,y = 0,z = -0.5,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 270.0000, rotationZ = 0.0000}
playfield_wall7 = GameObject:new{name = "playfield_wall7",mesh = "playfield_wall.obj",x = 2.5,y = 0,z = -0.5,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 270.0000, rotationZ = 0.0000}
CreateText = GameObject:new{name = "CreateText",mesh = "CreateText.obj",x = 3.2,y = 2,z = 32.5,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 155.4000, rotationZ = 0.0000}
CreditsText = GameObject:new{name = "CreditsText",mesh = "CreditsText.obj",x = 9.08,y = 1.46,z = 35.08,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 209.2484, rotationZ = 0.0000}
wall_text = GameObject:new{name = "wall_text",mesh = "wall_text.obj",x = 3,y = 2,z = 33,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 155.4000, rotationZ = 0.0000}
wall_text1 = GameObject:new{name = "wall_text1",mesh = "wall_text.obj",x = 0.9,y = 2,z = 28,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 90.0000, rotationZ = 0.0000}
wall_text2 = GameObject:new{name = "wall_text2",mesh = "wall_text.obj",x = 0.9,y = 2,z = 31.84,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 90.0000, rotationZ = 0.0000}
wall_text3 = GameObject:new{name = "wall_text3",mesh = "wall_text.obj",x = 0.9,y = 3.5,z = 24.128,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 90.0000, rotationZ = 0.0000}
wall_text4 = GameObject:new{name = "wall_text4",mesh = "wall_text.obj",x = 3,y = 4,z = 33,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 155.4000, rotationZ = 0.0000}
wall_text5 = GameObject:new{name = "wall_text5",mesh = "wall_text.obj",x = 3,y = 0,z = 33,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 155.4000, rotationZ = 0.0000}
wall_text6 = GameObject:new{name = "wall_text6",mesh = "wall_text.obj",x = 9.51,y = 3.46,z = 35.5,r = 0.8,g = 0.8,b = 0.8, rotationX = 359.0250, rotationY = 209.2503, rotationZ = 359.7772}
wall_text7 = GameObject:new{name = "wall_text7",mesh = "wall_text.obj",x = 1.83,y = 2,z = 23.54,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 29.7253, rotationZ = 269.7804}
wall_text8 = GameObject:new{name = "wall_text8",mesh = "wall_text.obj",x = 9.51,y = 1.46,z = 35.5,r = 0.8,g = 0.8,b = 0.8, rotationX = 359.0250, rotationY = 209.2503, rotationZ = 359.7772}
wall_text9 = GameObject:new{name = "wall_text9",mesh = "wall_text.obj",x = 9.01,y = 0.46,z = 26,r = 0.8,g = 0.8,b = 0.8, rotationX = 359.0250, rotationY = 287.0275, rotationZ = 359.7772}
wall_text10 = GameObject:new{name = "wall_text10",mesh = "wall_text.obj",x = 9.01,y = 1.96,z = 26,r = 0.8,g = 0.8,b = 0.8, rotationX = 359.0250, rotationY = 287.0275, rotationZ = 359.7772}
wall_text11 = GameObject:new{name = "wall_text11",mesh = "wall_text.obj",x = 9.01,y = 3.46,z = 26,r = 0.8,g = 0.8,b = 0.8, rotationX = 359.0250, rotationY = 287.0275, rotationZ = 359.7772}
wall_text12 = GameObject:new{name = "wall_text12",mesh = "wall_text.obj",x = 0.9,y = 3.5,z = 31.84,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 90.0000, rotationZ = 0.0000}
wall_text13 = GameObject:new{name = "wall_text13",mesh = "wall_text.obj",x = 0.9,y = 3.5,z = 28,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 90.0000, rotationZ = 0.0000}
wall_text14 = GameObject:new{name = "wall_text14",mesh = "wall_text.obj",x = 0.9,y = 2,z = 24.122,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 90.0000, rotationZ = 0.0000}
wall_1 = GameObject:new{name = "wall_1",mesh = "wall_1.obj",x = 3,y = 3,z = 33,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 155.4000, rotationZ = 0.0000}
wall_11 = GameObject:new{name = "wall_11",mesh = "wall_1.obj",x = 0.9,y = 4.5,z = 28,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 90.0000, rotationZ = 0.0000}
wall_12 = GameObject:new{name = "wall_12",mesh = "wall_1.obj",x = 0.9,y = 4.5,z = 24.128,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 90.0000, rotationZ = 0.0000}
wall_13 = GameObject:new{name = "wall_13",mesh = "wall_1.obj",x = 0.9,y = 5,z = 24.128,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 90.0000, rotationZ = 0.0000}
wall_14 = GameObject:new{name = "wall_14",mesh = "wall_1.obj",x = 0.9,y = 5,z = 28,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 90.0000, rotationZ = 0.0000}
wall_15 = GameObject:new{name = "wall_15",mesh = "wall_1.obj",x = 9.51,y = 2.46,z = 35.5,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 209.2484, rotationZ = 0.0000}
wall_16 = GameObject:new{name = "wall_16",mesh = "wall_1.obj",x = 0.9,y = 4.5,z = 31.84,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 90.0000, rotationZ = 0.0000}
wall_17 = GameObject:new{name = "wall_17",mesh = "wall_1.obj",x = 9.51,y = 0.46,z = 35.5,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 209.2484, rotationZ = 0.0000}
wall_18 = GameObject:new{name = "wall_18",mesh = "wall_1.obj",x = 0.9,y = 5,z = 31.84,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 90.0000, rotationZ = 0.0000}
wall_2 = GameObject:new{name = "wall_2",mesh = "wall_2.obj",x = 3,y = 1,z = 33,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 155.4000, rotationZ = 0.0000}
wall_26 = GameObject:new{name = "wall_26",mesh = "wall_2.obj",x = 0.9,y = 1,z = 31.84,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 90.0000, rotationZ = 0.0000}
wall_21 = GameObject:new{name = "wall_21",mesh = "wall_2.obj",x = 0.9,y = 1,z = 28,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 90.0000, rotationZ = 0.0000}
wall_22 = GameObject:new{name = "wall_22",mesh = "wall_2.obj",x = 0.9,y = 1,z = 24.122,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 90.0000, rotationZ = 0.0000}
wall_23 = GameObject:new{name = "wall_23",mesh = "wall_2.obj",x = 0.9,y = 0.2,z = 31.84,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 90.0000, rotationZ = 0.0000}
wall_24 = GameObject:new{name = "wall_24",mesh = "wall_2.obj",x = 0.9,y = 0.2,z = 24.122,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 90.0000, rotationZ = 0.0000}
wall_25 = GameObject:new{name = "wall_25",mesh = "wall_2.obj",x = 0.9,y = 0.2,z = 28,r = 0.8,g = 0.8,b = 0.8, rotationX = 0.0000, rotationY = 90.0000, rotationZ = 0.0000}
