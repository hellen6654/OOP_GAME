
namespace game_framework
{
	class Line
	{
	public:
		Line();	
		~Line();
		
		void DrawRailway(int, int, int, int);							//�e �X�y �D

		void SetLineColor(int,int,int);									//�]�w�u���C��
		void SetClickedStartStationNum(int);							//�]�wClickedStartStationNum
		void SetClickedEndStationNum(int);								//�]�wClickedEndStationNum
		void SetPassedStation(int,int);									//�]�w���g�L������

		int  GetClickedStartStationNum();								//���oClickedStartStationNum
		int  GetClickedEndStationNum();									//���oClickedEndStationNum
		int  GetMouseClickedStationNum(int,int,vector<Station>,int);	//���o�ƹ��I�쪺���Ө������s��
		int  GetLineColorNum();											//���o�u���C��s�� red=0 orange=1 ....
		int  GetClickedFirstStation();									//���o�u�������_�I
		int  GetClickedLastStation();									//���o�u���������I

		bool IsClickedStation(int, int, vector<Station>, int);			//�ˬd�O�_�I�쨮�� ���N�^��ture �p�G�S���h�^��false
		bool IsClickedTwoStation();										//�ˬd�O�_�w�g�I�F��Ө����F
		bool IsMouseClickedLineColorBMP(int,int);						//�ˬd�O�_�ƹ����I��U��u���C�⪺�Ϥ� //���u���C��n�Ϊ���
		bool IsPassedStationEmpty();
		

		void LoadBitmap();
		void ShowLineIconBitmap();
		void ShowRailway(vector<Station>,int);							//���X���u
	private:
		CMovingBitmap lineColorBMP;
		int clickedStartStationNum;
		int clickedEndStationNum;
		int lineColor[3];
		vector<int> passedStation;
		//red(255.0.0),orang(255.144.0),yellow(255.255.0),green(0.255.0),blue(0.138.255),bblue(0.6.255),puple(144.0.255)
	};

	
}