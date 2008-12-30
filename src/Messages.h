class AsyncMessage
{
 public:
  int type;
  String text;
  int data;
  AsyncMessage(int typ)
    {
	type=typ;
	text=String::empty;
	data=0;
    }
  AsyncMessage(int typ, int dat)
    {
      type=typ;
      data=dat;
      text=String::empty;
    }
  AsyncMessage(int typ, String txt)
    {
	type=typ;
	text=txt;
	data=0;
    }
  AsyncMessage(int typ, int dat, String txt)
    {
      type=typ;
      text=txt;
      data=dat;
    }
  ~AsyncMessage() {}
};
