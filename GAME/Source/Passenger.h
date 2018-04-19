
namespace game_framework
{
class Passenger
{
    public:
        Passenger();
        Passenger(int, int, int);
        void LoadBitmap();			//���J�ϧ�
        void SetXY(int, int);		//�]�w�y��
        int GetX();
        int GetY();
        void SetType(int);
        void RandomBuildPassenger(vector<Passenger>&, int, int, int, int);
        void OnShow();				//�N�ϧζK��e��
        ~Passenger();
    private:
        const int MAXIUM_PASSENGER = 10;					//�|�X�{�b�a�ϤW���u��10�ӭ���
        const int MAXIUM_PASSENGER_TYPE = 7;				//���ȼ˦��`�@��7�� 00~06
        const int MAX_GAME_MAP_SIDE_X = 770;			//��ڤW���C�����X�b�u����770
        const int MIN_GAME_MAP_SIDE_X = 30;			    //��ڤW���C�����X�b�q30�}�l
        const int MAX_GAME_MAP_SIDE_Y = 570;			//��ڤW���C�����Y�b�u����570
        const int MIN_GAME_MAP_SIDE_Y = 60;			    //��ڤW���C�����Y�b�q60�}�l
        int x, y;										//�ϧήy��
        int passengerType;								//��������
        CMovingBitmap passengerAnimation;					//�Q�ΰʵe�@�ϧ�



};
}



