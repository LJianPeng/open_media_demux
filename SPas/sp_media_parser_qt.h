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
		QTableWidgetItem * frame_idx;						//帧序号
		QTableWidgetItem * frame_type;						//帧类型
		QTableWidgetItem * frame_length;					//帧长度
		QTableWidgetItem * frame_raw_offset;				//帧偏移
		QTableWidgetItem * is_video;						//音视频类型
		QTableWidgetItem * frame_codec_type;				//编码类型

		QTableWidgetItem *	frame_resolution_width;			//分辨率（宽）
		QTableWidgetItem *	frame_resolution_height;		//分辨率（高）
		QTableWidgetItem * frame_rate;						//帧率
		QTableWidgetItem * frame_time_osd;					//时间戳
		QTableWidgetItem * frame_pix_fmt;					//码流格式 yuv
	}FrameItem, *PFrameItem;

	typedef struct Pakt{
		int16t pkt_offset;
		int16t pkt_size;
		QString pkt_str;
	}Pakt, *pPakt;

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
	void sp_parser_stream_info();//解析码流函数
	void sp_show_binary_text(QTableWidgetItem *item); //显示裸码流数据
	void sp_display_binary_hex(QTableWidgetItem *item);
	void on_FrameListTableWidget_customContextMenuRequested(QPoint pos);  //为QTableWidget添加右键菜单项,保存裸码流用
	int  sp_parser_packet(AVFormatContext *fmt_ctx ,AVCodecContext *pCodecContext, AVCodecParserContext *pParserContext, AVPacket *pkt);
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
