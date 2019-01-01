#include <qlabel.h>
#include <stdio.h>
#include "sp_media_parser.h"
#include "sp_media_parser_qt.h"

SPas::SPas(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//����������ͼ��
	setWindowIcon(QIcon(QStringLiteral(":/SPas/Resources/SPas.ico")));

	m_fmt_ctx = NULL;
	m_filePath = "";							//�ļ�·��+�ļ���

	setAcceptDrops(true);

	ui.FrameListTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);	//���ò��ɱ༭
	ui.FrameListTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);	//���õ���ѡ������
	ui.FrameListTableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection); /// ����Ϊ����ѡ�ж��Ŀ��
	ui.FrameListTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	//�����Ҽ��˵�
	ui.FrameListTableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	m_pMenu = new QMenu(ui.FrameListTableWidget);
	m_pAction = new QAction(QStringLiteral("����Ϊ������"), this);

	connect(ui.openFile, &QAction::triggered, this, [=](){
		m_filePath = QFileDialog::getOpenFileName(this, "openSelectFile");
		if (!m_filePath.isEmpty()){
			this->setWindowTitle("SPas(" + m_filePath + ")");
			sp_parser_stream_info();  //TODO
		}
	});

	connect(m_pAction, &QAction::triggered, this, [=](){
		sp_save_raw_stream();
	});

	connect(ui.actionabout, &QAction::triggered, this, [=](){
		sp_about_msg_btn();
	});

	connect(ui.FrameListTableWidget, &QTableWidget::itemDoubleClicked, this, &SPas::sp_display_binary_hex);

}

SPas::~SPas()
{

}

void SPas::on_FrameListTableWidget_customContextMenuRequested(QPoint pos){
	m_pMenu->addAction(m_pAction);
	m_pMenu->exec(QCursor::pos());
}

void SPas::sp_clear_pakt_data(){
	for (QList<pPakt>::iterator ite = m_PaktList.begin(); ite != m_PaktList.end(); ite++){
		if (*ite){
			delete *ite;
			*ite = NULL;
		}
	}
	m_PaktList.clear();
}


void SPas::sp_clear_frame_item(){
	int rowCount = ui.FrameListTableWidget->rowCount();
	int colCount = ui.FrameListTableWidget->columnCount();
	QTableWidgetItem *pCol = NULL;
	for (int i = 0; i < rowCount; i++)
	{

		for (int j = 0; j < colCount; j++)
		{
			pCol = ui.FrameListTableWidget->item(i, j);
			delete pCol;
			pCol = NULL;
		}
		ui.FrameListTableWidget->removeRow(i);
	}
	ui.FrameListTableWidget->clearContents();
} 

void SPas::sp_save_raw_stream(){
	int col;
	FILE *pFin, *pFout;
	QFileDialog saveFileDialog;
	QString outFileName = saveFileDialog.getSaveFileName(this, tr("Open File"), "./", tr("File(*.*)"));
	std::string fileNameStr = m_filePath.toStdString();
	const int8t *inFileName = fileNameStr.c_str();

	/*pFin = fopen(inFileName, "rb");
	if (!pFin){
		printf("Count not open %s\n", inFileName);
		return;
	}*/

	pFout = fopen(outFileName.toStdString().c_str(), "wb");
	if (!pFout)	{
		printf("Count not open %s\n", outFileName);
		return;
	}

	int iSctRows;
	QTableWidgetItem *item;
#if 0
	//QList<QTableWidgetItem *> items = ui.FrameListTableWidget->selectedItems();
	int itemCols = ui.FrameListTableWidget->columnCount();//ÿһ��item������������
	QList<QTableWidgetSelectionRange>ranges = ui.FrameListTableWidget->selectedRanges();//��ȡѡ�е�����
	int iSctRows = ranges.count();//ѡ�е�����
	QTableWidgetItem *item;

	std::vector<int> vecItemIdx;
	for (int row = 0; row < iSctRows; row++){
		int rowNum = ranges.at(row).topRow();//ѡ�е�������
		vecItemIdx.push_back(rowNum);
	}
	std::sort(vecItemIdx.begin(), vecItemIdx.end());//��ѡ�е��н�������������
#else
	std::vector<int> vecItemIdx;//����ѡ���е�����
	QItemSelectionModel *selections = ui.FrameListTableWidget->selectionModel(); //���ص�ǰ��ѡ��ģʽ  
	QModelIndexList selectedsList = selections->selectedRows(); //��������ѡ����ģ����Ŀ�����б�  

	iSctRows = selectedsList.count();//ѡ�е����� 
	for (int i = 0; i < selectedsList.count(); i++)
	{
		vecItemIdx.push_back(selectedsList.at(i).row());
	}
	std::sort(vecItemIdx.begin(), vecItemIdx.end());
	//vecItemIdx.erase(std::unique(vecItemIdx.begin(), vecItemIdx.end()), vecItemIdx.end());

#endif
	

	AVPacket opkt;
	av_init_packet(&opkt);
	
	for (int row = 0; row < iSctRows; row++){
		int rowNum = vecItemIdx[row];//ranges.at(row).topRow();//ѡ�е�������
		item = ui.FrameListTableWidget->item(rowNum, 3);//��ȡ��ѡ����Ӧ�е�����

#if TRYVERSION
		if (rowNum > 50){
			sp_warning_msg_btn();
			continue;
		}
#endif
		int frame_offset = item->text().toInt(NULL, 10);//stringת��Ϊ����

		item = ui.FrameListTableWidget->item(rowNum, 2);
		int frame_size = item->text().toInt(NULL, 10);

		uint8t *frame_buf = (uint8t *)malloc(frame_size*sizeof(uint8t));

		fseek(m_videoParse.m_pFile, frame_offset, SEEK_SET);
		fread(frame_buf, 1, frame_size, m_videoParse.m_pFile);

		opkt.data = frame_buf;
		opkt.size = frame_size;
		do_packet_auto_bsf(m_fmt_ctx, &opkt);

		//av_bitstream_filter_filter(h264bsfc, ifmt_ctx->streams[videoindex]->codec, NULL, &pkt.data, &pkt.size, pkt.data, pkt.size, 0);


		fwrite(opkt.data, 1, opkt.size*sizeof(uint8t), pFout);
		fflush(pFout);
		free(frame_buf);
	}

	//fclose(pFin);
	fclose(pFout);	
	//ui.FrameListTableWidget->clearSelection();//ȡ������ѡ�е���

}

void SPas::sp_show_binary_text(QTableWidgetItem *item)
{
	int ret;
	int itemRow = item->row();
	ui.FrameShowBinaryText->setText("");
	pPakt pakt = m_PaktList.at(itemRow);

	int filePosOrg = ftell(m_videoParse.m_pFile);
	fseek(m_videoParse.m_pFile, pakt->pkt_offset, SEEK_SET);
	uint8t *pPaktData = new uint8t[pakt->pkt_size];
	fread(pPaktData, 1, pakt->pkt_size, m_videoParse.m_pFile);
	fseek(m_videoParse.m_pFile, filePosOrg, SEEK_SET);

	QString pkt_str = QString("%1\t").arg(0, 8, 16, QChar('0'));
	if (pakt->pkt_str.isEmpty())
	{
		for (int i = 0; i < pakt->pkt_size; i++)
		{
			if (i % 16 == 0 && i)
			{
				pkt_str += "\n";
				pkt_str += QString("%1\t").arg(i, 8, 16, QChar('0'));
			}
			pkt_str += QString("%1 ").arg((unsigned char)pPaktData[i], 2, 16, QChar('0'));
		}
		pakt->pkt_str = pkt_str;
	}
	ui.FrameShowBinaryText->setText(pakt->pkt_str);


	ui.FrameListTableWidget->clearSelection();//ȡ������ѡ�е���
}


int8t hexToascii(uint8t c)
{
	if (c >= 128 || c <= 32)
		return '.';
	else
		return c;
}

#define DISPLAYHEXROW		16   //һ����ʾ���ٸ�binary
void SPas::sp_display_binary_hex(QTableWidgetItem *item)
{
	int itemRow = item->row();
	ui.FrameShowBinaryText->setText("");
	pPakt pakt = m_PaktList.at(itemRow);

	//int filePosOrg = ftell(m_videoParse.m_pFile);
	fseek(m_videoParse.m_pFile, pakt->pkt_offset, SEEK_SET);
	uint8t *pPaktData = new uint8t[pakt->pkt_size];
	fread(pPaktData, 1, pakt->pkt_size, m_videoParse.m_pFile);
	//fseek(m_videoParse.m_pFile, filePosOrg, SEEK_SET);

	AVPacket opkt;
	av_init_packet(&opkt);
	opkt.data = pPaktData;
	opkt.size = pakt->pkt_size;
	do_packet_auto_bsf(m_fmt_ctx, &opkt);


	int posIndex = 0;
	int displayRows = pakt->pkt_size / DISPLAYHEXROW + (pakt->pkt_size % DISPLAYHEXROW == 0 ? 0 : 1);
	QString pkt_str;
	for (int ir = 0; ir < displayRows; ir++)
	{
		QString str3, str1, str2;
		int oneRowNum = (ir + 1) * DISPLAYHEXROW > pakt->pkt_size ? (pakt->pkt_size - ir * DISPLAYHEXROW) : DISPLAYHEXROW;
		
		pkt_str += QString("%1\t").arg(ir, 8, 16, QChar('0'));
		for (int ic = 0; ic < oneRowNum; ic++)
		{
			QString tmp;
			tmp.sprintf("%02x ", opkt.data[posIndex]);
			str1.append(tmp);
			tmp.sprintf("%c", hexToascii(opkt.data[posIndex]));
			str2.append(tmp);
			posIndex++;
		}
		if (oneRowNum < DISPLAYHEXROW)
		{
			for (int x = 0; x < DISPLAYHEXROW - oneRowNum; x++)
			{
				str1 += "   ";
			}
		}
		pkt_str += str1 + "    " + str2 + "\n";
	}
	ui.FrameShowBinaryText->setText(pkt_str);
	//ui.FrameListTableWidget->clearSelection();//ȡ������ѡ�е���
}