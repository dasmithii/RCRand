class Bytemap {
  
  int i = 0;
  PImage img;
  
  Bytemap(){
    img = createImage(width, height, RGB);
  }
  
  void register(int val){
    if(i >= width * height)
      i = 0;
    img.pixels[i] = color(val);
    ++i;
  }
  
  void draw(){
    img.updatePixels();
    image(img, 0, 0, width, height); 
  }
}
