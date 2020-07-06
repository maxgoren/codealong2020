Gui::Gui(int mx, int my, int mw, int mh, int sw, int sh)
{
 this->mapX = mx;
 this->mapY = my;
 this->mapW = mw;
 this->mapH - mh;
 this->scrW = sw;
 this->scrH = sh;
}



void Gui::fade(int x,int y,int start[3],int fin[3],char *message)
{
 // :)
 int i;
 int stepping = strlen(message);
 int distance[3] = {(fin[0] - start[0])/stepping,
 		    (fin[1] - start[1])/stepping,
 		    (fin[2] - start[3])/stepping,};
 int color[3] = {start[0], start[1], start[2]};
 terminal_layer(3);
 for (i = 0; i < stepping; i++)
 {
  color[0] = color[0] + distance[0];
  color[1] = color[1] + distance[1];
  color[2] = color[2] + distance[2];
  terminal_color(color_from_argb(255, color[0], color[1], color[2]));
  terminal_print(x+i, y, message + i);
 }
}

void Gui::banner(std::vector<std::string>* gamelog)
{
 std::vector<std::string>::iterator it;
 int x, y;
 char *title = "aT's adventure in bitLand";
 int i;
 int start[3] = {128,128,128};
 int fin[3] = {0,255,255};
 fade(scrW/2 - strlen(title)/2, 1, start, fin, title);
 terminal_layer(2);
 terminal_color("red");
 terminal_print(4,1,"Message Log");
 terminal_print(2,2,"[U+250F]");
 terminal_print(2,3,"[U+2503]");
 terminal_print(2,4,"[U+2503]");
 terminal_print(2,5,"[U+2517]");
 terminal_print(scrW-3,2,"[U+2513]");
 terminal_print(scrW-3,3,"[U+2503]");
 terminal_print(scrW-3,4,"[U+2503]");
 terminal_print(scrW-3,5,"[U+251B]");
 for (x = 3; x < scrW - 3; x++)
 {
  terminal_print(x,2, "[U+2501]"); 
  terminal_print(x,5, "[U+2501]");
 }

std::cout<<gamelog->size()<<"\n";
//std::cout<<*it<<"\n";
if (gamelog->size() == 1) {
std::cout<<"boyyy... "<<gamelog->at(0)<<"\n";
 terminal_printf(4,3,"%s", gamelog->at(0).c_str());
}
if (gamelog->size() > 1) {
 for (i = 0; i < gamelog->size() - 1; i++)
 {
  terminal_printf(4, 3, "%s", gamelog->at(i).c_str());
  terminal_printf(4, 4, "%s", gamelog->at(i+1).c_str());
 }
}
}


void Gui::drawGui(std::vector<std::string>* gamelog)
{
 int x, y;
 //Top five rows for banner/message log section
 terminal_layer(0); //we can set bgcolor on terminal_layer 0 to make a "frame"
 for (x = 0; x < scrW; x++) {
  for (y = 0; y < scrH; y++) {  
   terminal_bkcolor("black");
    terminal_print(x, y, " ");
    terminal_bkcolor("#cecece");
    terminal_print(x, 0, " ");
    terminal_print(x, 6, " ");
    terminal_print(x, scrH, " "); 
   terminal_print(0, y, " ");
   terminal_print(mapW + 1, y+6, " ");
   terminal_print(scrW-1, y, " ");
 }
}
banner(gamelog);
terminal_bkcolor("#cecece");
terminal_print(1,6, " ");
}
