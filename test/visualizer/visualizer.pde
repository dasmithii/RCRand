BufferedReader reader;
String line;
int i = 0;
 
void setup() {
  reader = createReader("out.txt");    
  size(1000, 1000);
}
 
void getPoint(){
  try {
    line = reader.readLine();
  } catch (IOException e) {
    e.printStackTrace();
    line = null;
  }

  if (line == null) {
    noLoop();  
  } else {
    int val = int(line);
    int x = i % width;
    int y = i / width;
    fill(val); stroke(val);
    point(x, y);
    i++;
  }
} 

void draw() {
  for(int i = 0; i < 1000; ++i)
    getPoint();
} 



