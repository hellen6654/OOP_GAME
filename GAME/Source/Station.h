
namespace game_framework
{
	class Station
	{
	public:
		Station();
		Station(int, int, int);
		void LoadBitmap();			//���J�ϧ�
		void SetXY(int, int);		//�]�w�y��
		void SetPassenagerNum(int); //�]�w�ثe���ȼƶq
		void SetAddPassenagerNum(int); //�]�w�W�[�ثe���ȼƶq
		int GetX();
		int GetY();
		int GetCenterPositionX();
		int GetCenterPositionY();
		int GetPassenagerNum();
		void SetType(int);
		void RandomBuildStation(vector<Station>&);
		void CheckedOverLappingStation(vector<Station>&);
		void OnShow();				//�N�ϧζK��e��
		~Station();
	private:
		const int MAXIUM_STATION = 10;					//�|�X�{�b�a�ϤW���u��10�Ө���
		const int MAXIUM_STATION_TYPE = 7;				//�����˦��`�@��7�� 00~06
		//mygame.h �̭��]���ۦP���ݩʭn��
		const int MAX_GAME_MAP_SIDE_X = 770;			//��ڤW���C�����X�b�u����770 
		const int MIN_GAME_MAP_SIDE_X = 30;			    //��ڤW���C�����X�b�q30�}�l
		const int MAX_GAME_MAP_SIDE_Y = 560-25;			//��ڤW���C�����Y�b�u����560
		const int MIN_GAME_MAP_SIDE_Y = 60;			    //��ڤW���C�����Y�b�q60�}�l

		const int centerPositionX;						//����X�y��
		const int centerPositionY;						//����Y�y��
		int x, y;										//�ϧήy��
		int stationType;								//��������
		int passenagerNum;								//�`�@���X�ӭ��Ȧb����

		CMovingBitmap stationAnimation;					//�Q�ΰʵe�@�ϧ�
				
	};
}

