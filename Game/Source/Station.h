
namespace game_framework
{
	class Station
	{
	public:
		Station();
		Station(int,int,int);
		void LoadBitmap();			//���J�ϧ�
		void SetXY(int, int);		//�]�w�y��
		int GetX();
		int GetY();
		void SetType(int);
		bool IsClicked();
		void setClicked(bool flag);
		void OnShow();				//�N�ϧζK��e��
		~Station();
	private:
		int x, y;					//�ϧήy��
		int station_type;			//��������
		bool isClicked;
		CMovingBitmap station_animation;	//�Q�ΰʵe�@�ϧ�
	};
}


