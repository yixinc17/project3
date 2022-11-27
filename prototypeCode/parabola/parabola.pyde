posX = -400
posY = posX**2
posXX = 400
posYY = posXX**2
def setup():
    size(800,600)
    
def draw():
    background(174,98,200)
    # global posX
    # global posY
    # fill(237,200,17)
    # ellipse(posX+400,posY,40,40)
    # posX = posX + 4
    # posY = posX**2/250
    # if posX > 400:
    #     posX = -400
        
    global posXX
    global posYY
    fill(0,200,17)     
    ellipse(posXX+400,posYY,40,40)
    posXX = posXX - 4
    posYY = posYY**2/250
    if posXX < 400:
        posXX = 400
