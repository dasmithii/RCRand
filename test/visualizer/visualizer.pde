BufferedReader reader;
String line;
int i = 0;
Bytemap map;
Distribution dist;
 
void setup() {
  reader = createReader("out.txt"); 
  size(1000, 1000);
  map = new Bytemap();
  dist = new Distribution();
}
 
void getPoint(){
  try {
    line = reader.readLine();
  } catch (IOException e) {
    e.printStackTrace();
    line = null;
  }

  if (line == null) {
  } else {
    int val = int(line);
    map.register(val);
    dist.register(val);
  }
} 

void draw() {
  for(int i = 0; i < 1000; ++i)
    getPoint();
  map.draw();
  dist.draw(0, 0, 300, 200);
} 



