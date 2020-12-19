#include "stdafx.h"

namespace Error
{
	ERROR errors[ERROR_MAX_ENTRY] =
	{
		//0-100 - ��������� ������
		ERROR_ENTRY(0, "SYSTEM ������������ ��� ������"),
		ERROR_ENTRY(1, "SYSTEM ��������� ����"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40),
		ERROR_ENTRY_NODEF10(50), ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),



		ERROR_ENTRY(100, "SYSTEM �������� -in ������ ���� �����"),
		ERROR_ENTRY(101, "SYSTEM ��������� ����� �������� ���������"),
		ERROR_ENTRY(102, "SYSTEM ������ ��� �������� ����� � �������� �����(-in)"),
		ERROR_ENTRY(103, "SYSTEM ������ ��� �������� ����� ���������(-log)"),
		ERROR_ENTRY_NODEF(104), ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107), ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY_NODEF10(110), ERROR_ENTRY_NODEF10(120), ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140),
		ERROR_ENTRY_NODEF10(150), ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),



		//200 - ����������� ������
		ERROR_ENTRY(200, "-LEX-200 ������������ ������ � �������� �����(-in)"),
		ERROR_ENTRY(201, "-LEX-201 ����������� ������������������ ��������"),
		ERROR_ENTRY(202, "-LEX-202 �������� ������ ������� ������"),
		ERROR_ENTRY(203, "-LEX-203 �������� ������ ������� ���������������"),
		ERROR_ENTRY_NODEF(204, "LEX-204 �������� �����������"),
		ERROR_ENTRY_NODEF(205, "LEX-205 ������������ ����"),
		ERROR_ENTRY_NODEF(206), ERROR_ENTRY_NODEF(207), ERROR_ENTRY_NODEF(208), ERROR_ENTRY_NODEF(209),
		ERROR_ENTRY_NODEF10(210), ERROR_ENTRY_NODEF10(220), ERROR_ENTRY_NODEF10(230), ERROR_ENTRY_NODEF10(240),
		ERROR_ENTRY_NODEF10(250), ERROR_ENTRY_NODEF10(260), ERROR_ENTRY_NODEF10(270), ERROR_ENTRY_NODEF10(280), ERROR_ENTRY_NODEF10(290),



		//300 - ������������� ������
		ERROR_ENTRY(300, "-SEM-300 ������������� �� ��������"),
		ERROR_ENTRY(301, "-SEM-301 ����������� ����� ����� main"),
		ERROR_ENTRY(302, "-SEM-302 ��������� ����� ����� main"),
		ERROR_ENTRY(303, "-SEM-303 �� ������ ��� �������������� ��� ����������"),
		ERROR_ENTRY(304, "-SEM-304 ����������� �������� ����� type ��� ����������"),
		ERROR_ENTRY(305, "-SEM-305 ������� ��������������� ��������������"),
		ERROR_ENTRY(306, "-SEM-306 ��������� ������������ ���������� ���������� �������"),
		ERROR_ENTRY(307, "-SEM-307 ������� ����� ���������� � ������ �������"),
		ERROR_ENTRY(308, "-SEM-308 ���-�� ��������� �������� � ������������ ���������� �� ���������"),
		ERROR_ENTRY(309, "-SEM-309 ������������ ����� ������������ ����������"),
		ERROR_ENTRY(310, "-SEM-310 ������������� ������� ���������� �������� �����������"),
		ERROR_ENTRY(311, "-SEM-311 ��������� ������ \'\"\'. ��������, �� ������ ��������� �������"),
		ERROR_ENTRY(312, "-SEM-312 �������� ������ ���������� ��������"),
		ERROR_ENTRY(313, "-SEM-313 ������������ ������������� �������"),
		ERROR_ENTRY(314, "-SEM-314 ���� ������ � ��������� �� ���������"),
		ERROR_ENTRY(315, "-SEM-315 ��� ������� � ������������� �������� �� ���������"),
		ERROR_ENTRY(316, "-SEM-316 ������������ ��������� ��������� ����� \'=\'"),

		ERROR_ENTRY_NODEF(317),
		ERROR_ENTRY_NODEF(318), ERROR_ENTRY_NODEF(319),
		ERROR_ENTRY_NODEF10(320),ERROR_ENTRY_NODEF10(330),ERROR_ENTRY_NODEF10(340),ERROR_ENTRY_NODEF10(350),
		ERROR_ENTRY_NODEF10(360),ERROR_ENTRY_NODEF10(370),ERROR_ENTRY_NODEF10(380),ERROR_ENTRY_NODEF10(390),
		ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500),
		//600 - �������������� ������
		ERROR_ENTRY(600, "-SYN-600 ������. �������� ��������� ���������"),
		ERROR_ENTRY(601, "-SYN-601 ������. �� ������ ������ ���������� �������"),
		ERROR_ENTRY(602, "-SYN-602 ������ � ���� �������"),
		ERROR_ENTRY(603, "-SYN-603 ������ � ���� ���������"),
		ERROR_ENTRY(604, "-SYN-604 ������ � ������ ���������� �������"),
		ERROR_ENTRY(605, "-SYN-605 ������ � ������ �������/���������"),
		ERROR_ENTRY(606, "-SYN-606 ������ � ������ ����������� ���������� �������"),
		ERROR_ENTRY(607, "-SYN-607 ������. �������� �������������� ��������"),
		ERROR_ENTRY(608, "-SYN-608 ������. �������� ���������. ��������� ������ ��������������/��������"),
		ERROR_ENTRY(609, "-SYN-609 ������ � �������������� ���������"),
		ERROR_ENTRY(610, "-SYN-610 ������. ������������ �������������� �����������"),

		ERROR_ENTRY_NODEF10(620), ERROR_ENTRY_NODEF10(630), ERROR_ENTRY_NODEF10(640), ERROR_ENTRY_NODEF10(650),
		ERROR_ENTRY_NODEF10(660), ERROR_ENTRY_NODEF10(670), ERROR_ENTRY_NODEF10(680), ERROR_ENTRY_NODEF10(690),
		ERROR_ENTRY_NODEF100(700), ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900)
	};

	ERROR GetError(int id)
	{
		if (id < 0 || id > ERROR_MAX_ENTRY)
			return errors[0];
		else
			return errors[id];
	}

	ERROR GetError(int id, int line, int cells)
	{
		ERROR err = GetError(id);
		err.position.cells = cells;
		err.position.line = line;
		return err;
	}
};