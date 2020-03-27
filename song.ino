int speakerPin = 2;
const int echo=8; 
const int trig=9;  

char notes[] = "ggagCb ggagDC ggGECba FFECDC";// 決定每個音階的拍子
unsigned long beats[] = {1,1,2,2,2,2,2,1,1,2,2,2,2,2,1,1,2,2,2,2,2,1,1,2,2,2,2,2,2};
int length = sizeof(notes);  // 利用 sizeof()，算出總共要多少音符





void setup() 
{
  pinMode(speakerPin, OUTPUT);
  pinMode(trig,OUTPUT); //設定數位接腳9 為輸出模式。
  pinMode(echo,INPUT); //設定數位接腳8 為接收模式。
}

void loop() 
{
  int tempo;
  
  // 利用 for 來播放我們設定的歌曲，一個音一個音撥放
  for (int i = 0; i < length; i++) {
  // 如果是空白的話，不撥放音樂
    tempo = ping(trig, echo); // 透過距離決定一拍多長
    if (notes[i] == ' ') 
    {
      delay(beats[i] * tempo * 5); // rest
    } 
    else 
    {
      // 呼叫 palyNote() 這個 function，將音符轉換成訊號讓蜂鳴器發聲
      playNote(speakerPin,notes[i], beats[i] * tempo * 5);
    }

    delay(tempo * 5);
  }
}

void playNote(int OutputPin, char note, unsigned long duration) 
{
  // 音符字元與對應的頻率由兩個矩陣表示
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C','D','E','F','G' };
  int tones[] = { 261, 294, 330, 349, 392, 440, 494, 523,587,659,698,784 };
  // 播放音符對應的頻率
  for (int i = 0; i < 12; i++) 
  {
    if (names[i] == note)
    {
      tone(OutputPin,tones[i], duration);
      //下方的 delay() 及 noTone ()，測試過後一定要有這兩行，整體的撥放出來的東西才不會亂掉，可能是因為 Arduino 送出tone () 頻率後會馬上接著執行下個指令，不會等聲音播完，導致撥出的聲音混合而亂掉
      delay(duration);
      noTone(OutputPin);
    }
  }
}

int ping(int trig, int echo){
  unsigned long cm; //距離(單位:公分)。
  unsigned long duration; //脈寬(單位:微秒)。
  pinMode(trig,OUTPUT); //設定數位接腳 2為輸出模式。
  digitalWrite(trig,LOW); //輸出脈寬 5µs的脈波啟動PING)))。
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(5);
  digitalWrite(echo,LOW);
  pinMode(echo,INPUT); //設定數位接腳 2為輸入模式。
  duration=pulseIn(echo,HIGH); //讀取與物體距離成正比的脈波HIGH時間。
  cm=duration/29/2; //計算物體距離(單位:公分)。
  if (cm < 100)
    return cm; //傳回物體距離(單位:公分)
} 
