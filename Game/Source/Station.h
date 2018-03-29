
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
		void OnShow();				//�N�ϧζK��e��
		~Station();
	private:
		int x, y;					//�ϧήy��
		int station_type;			//��������
		CMovingBitmap station_animation;	//�Q�ΰʵe�@�ϧ�
	};
}


