//
//
// "Misc Options" Tab for KFM configuration
//
// (c) Sven Radej 1998
// (c) David Faure 1998

#include <qlabel.h>
#include <qgroupbox.h>
#include <qlayout.h>//CT - 12Nov1998
#include <kapp.h>

#include "miscopts.h"

#include <konqdefaults.h> // include default values directly from konqueror
#include <klocale.h>
#include <kconfig.h>


//-----------------------------------------------------------------------------

KMiscOptions::KMiscOptions(KConfig *config, QString group, QWidget *parent, const char *name )
    : KCModule( parent, name ), g_pConfig(config), groupname(group)
{
    QVBoxLayout *lay = new QVBoxLayout(this, 40 /* big border */, 20);

    urlpropsbox = new QCheckBox(i18n("&Allow per-URL settings"), this);
    lay->addWidget(urlpropsbox);
    connect(urlpropsbox, SIGNAL(clicked()), this, SLOT(changed()));

    QHBoxLayout *hlay = new QHBoxLayout(10);
    lay->addLayout(hlay);
    QLabel * label = new QLabel(i18n("Terminal"),this);
    hlay->addWidget(label, 1);

    leTerminal = new QLineEdit(this);
    hlay->addWidget(leTerminal, 5);
    connect(leTerminal, SIGNAL(textChanged(const QString&)), this, SLOT(changed()));

    m_pHaveBiiigToolBarCheckBox = new QCheckBox( i18n( "Display big toolbar" ),
                                                 this );
    connect(m_pHaveBiiigToolBarCheckBox, SIGNAL(clicked()), this, SLOT(changed()));
						
    lay->addWidget( m_pHaveBiiigToolBarCheckBox );

    lay->addStretch(10);
    lay->activate();

    load();
}

void KMiscOptions::load()
{
    // *** load ***
    g_pConfig->setGroup( "Misc Defaults" );
    bool bUrlprops = g_pConfig->readBoolEntry( "EnablePerURLProps", false);
    QString sTerminal = g_pConfig->readEntry( "Terminal", DEFAULT_TERMINAL );
    bool bHaveBigToolBar = g_pConfig->readBoolEntry( "HaveBigToolBar", false );

    // *** apply to GUI ***

    urlpropsbox->setChecked(bUrlprops);
    leTerminal->setText(sTerminal);
    m_pHaveBiiigToolBarCheckBox->setChecked( bHaveBigToolBar );
}

void KMiscOptions::defaults()
{
    urlpropsbox->setChecked(false);
    leTerminal->setText(DEFAULT_TERMINAL);
    m_pHaveBiiigToolBarCheckBox->setChecked( false );
}

void KMiscOptions::save()
{
    g_pConfig->setGroup( "Misc Defaults" );
    g_pConfig->writeEntry( "EnablePerURLProps", urlpropsbox->isChecked());
    g_pConfig->writeEntry( "Terminal", leTerminal->text());
    g_pConfig->writeEntry( "HaveBigToolBar", m_pHaveBiiigToolBarCheckBox->isChecked() );
    g_pConfig->sync();
}

void KMiscOptions::changed()
{
    emit KCModule::changed(true);
}

#include "miscopts.moc"
