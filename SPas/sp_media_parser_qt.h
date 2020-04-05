#ifndef _SP_MEDIA_PARSER_QT_H_
#define _SP_MEDIA_PARSER_QT_H_
#include <QFileDialog>
#include <QtWidgets/QMainWindow>
#include <stdint.h>

#include "sp_public_def.h"
#include "sp_media_parser.h"
#include "ui_sp_media_parser_qt.h"


class SPas : public QMainWindow
{
	Q_OBJECT

public:
	typedef struct FrameItem{
		QTableWidgetItem * frame_idx;						//֡���
		QTableWidgetItem * frame_type;						//֡����
		QTableWidgetItem * frame_length;					//֡����
		QTableWidgetItem * frame_raw_offset;				//֡ƫ��
		QTableWidgetItem * is_video;						//����Ƶ����
		QTableWidgetItem * frame_codec_type;				//��������

		QTableWidgetItem *	frame_resolution_width;			//�ֱ��ʣ���
		QTableWidgetItem *	frame_resolution_height;		//�ֱ��ʣ��ߣ�
		QTableWidgetItem * frame_rate;						//֡��
		QTableWidgetItem * frame_time_osd;					//ʱ���
		QTableWidgetItem * frame_pix_fmt;					//������ʽ yuv
	}FrameItem, *PFrameItem;

	typedef struct Pakt{
		int16t pkt_realOffset;								//��������ʼƫ�ƣ���ʽ��װ�㣩
		int16t pkt_realSize;								//�����ݵĳ���
		int16t pkt_offset;										//ԭʼ���ݵ���ʼƫ��
		int16t pkt_size;										//ԭʼ���ݵĳ���
		QString pkt_str;
	}Pakt, *pPakt;

	bool  m_b_set_show_raw;									//����ʾ�����Ƿ���ʾ������

public:
	SPas(QWidget *parent = 0);
	~SPas();
	void sp_clear_pakt_data();
	void sp_clear_frame_item();
	void sp_save_raw_stream();

protected:
	void dragEnterEvent(QDragEnterEvent *e);
	void dropEvent(QDropEvent *e);

public slots:
	void sp_about_msg_btn();
	void sp_parser_stream_info();//������������
	void sp_show_binary_text(QTableWidgetItem *item); //��ʾ����������
	void sp_display_binary_hex(QTableWidgetItem *item);
	void on_FrameListTableWidget_customContextMenuRequested(QPoint pos);  //ΪQTableWidget����Ҽ��˵���,������������
	int  sp_parser_packet(AVFormatContext *fmt_ctx ,AVCodecContext *pCodecContext, AVCodecParserContext *pParserContext, AVPacket *pkt);
	
	//��ʾ��������ť�¼�
	void sp_set_show_raw_stream(bool flag);

private:
	Ui::SPasClass ui;
	QString m_filePath;
	VideoParser m_videoParse;
	QList<pPakt> m_PaktList;

	AVFormatContext *m_fmt_ctx;

	QMenu *m_pMenu;
	QAction *m_pAction;
};

#endif // SPAS_H
