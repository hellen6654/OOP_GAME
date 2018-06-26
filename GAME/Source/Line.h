
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
		void SetLinePointXY(vector<Station>);							//�]�w����I��XY�y��

		int  GetClickedStartStationNum();								//���oClickedStartStationNum
		int  GetClickedEndStationNum();									//���oClickedEndStationNum
		int  GetMouseClickedStationNum(int,int,vector<Station>,int);	//���o�ƹ��I�쪺���Ө������s��
		void GetLineColorRGB(int& R, int& G, int& B);					//���o�u���C��RGB
		int  GetLineColor();											//���o�u���C��s�� red=0 orange=1 ....
		int  GetClickedFirstStation();									//���o�u�������_�I
		int  GetClickedLastStation();									//���o�u���������I
		void GetLinePointXY(vector<int>&,vector<int>&);
		void GetPassedStationNum(vector<int>&);
		void GetTotalPassedStation(int(&num)[6]);
		void Reset();

		bool IsClickedStation(int, int, vector<Station>, int);			//�ˬd�O�_�I�쨮�� ���N�^��ture �p�G�S���h�^��false
		bool IsClickedTwoStation();										//�ˬd�O�_�w�g�I�F��Ө����F

		bool IsMouseClickedLineColorBMP(int,int);						//�ˬd�O�_�ƹ����I��U��u���C�⪺�Ϥ� //���u���C��n�Ϊ���
		bool IsPassedStationEmpty();									//�ˬd�O�_���b�a�ϤW�ԥX�u���F
		void CountTotalPassedStation();									//�p��u���Ҹg�L����������
		void LoadBitmap();						
		void ShowLineIconBitmap();										//��ܵe�����������Ϥ�icon
		void ShowRailway(vector<Station>);								//���X�u��
		bool IsIconCanBeClicked();
		void SetIsCanbeClicked(bool b);
		bool IsClicked();
		void SetIsClicked(bool b);
	private:
		CMovingBitmap lineColorBMP;
		int clickedStartStationNum;
		int clickedEndStationNum;
		int lineColor[3];
		bool isCanBeClicked;
		bool isClicked = false;
		int totalPassedStationNum[6] = {0};							//�u���Ҹg�L����������
		vector<int> passedStation;									//�g�L���������s��
		vector<int> linePointX;										//���X�u���I��X�y�� �PlineYPoint�s��
		vector<int> linePointY;										//���X�u���I��Y�y�� �PlineXPoint�s��
		//red(255.0.0),orang(255.144.0),yellow(255.255.0),green(0.255.0),blue(0.138.255),bblue(0.6.255),puple(144.0.255)
	};

	
}