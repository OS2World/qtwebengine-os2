/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtWebEngine module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef BROWSER_MESSAGE_FILTER_QT_H
#define BROWSER_MESSAGE_FILTER_QT_H

#include "base/callback.h"
#include "content/public/browser/browser_message_filter.h"

class GURL;
class Profile;

namespace QtWebEngineCore {

class ProfileIODataQt;

class BrowserMessageFilterQt : public content::BrowserMessageFilter
{
public:
    BrowserMessageFilterQt(int render_process_id, Profile *profile);

private:
    bool OnMessageReceived(const IPC::Message& message) override;


    void OnAllowStorageAccess(int render_frame_id,
                              const GURL &origin_url,
                              const GURL &top_origin_url,
                              int storage_type,
                              bool *allowed);

    void OnRequestStorageAccessSync(int render_frame_id,
                                    const GURL &origin_url,
                                    const GURL &top_origin_url,
                                    int storage_type,
                                    IPC::Message *message);
    void OnRequestStorageAccessAsync(int render_frame_id,
                                     int request_id,
                                     const GURL &origin_url,
                                     const GURL &top_origin_url,
                                     int storage_type);
    void OnRequestStorageAccessSyncResponse(IPC::Message *reply_msg,
                                            bool allowed);
    void OnRequestStorageAccessAsyncResponse(int render_frame_id,
                                             int request_id,
                                             bool allowed);
    void OnRequestStorageAccess(int render_frame_id,
                                const GURL &origin_url,
                                const GURL &top_origin_url,
                                int storage_type,
                                base::Callback<void(bool)> callback);

    ProfileIODataQt *m_profileData;
};

} // namespace QtWebEngineCore

#endif // BROWSER_MESSAGE_FILTER_QT_H
