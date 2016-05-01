/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Copyright (C) 2016 ScyllaDB
 *
 * Modified by ScyllaDB
 */

/*
 * This file is part of Scylla.
 *
 * Scylla is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Scylla is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Scylla.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "authorizer.hh"

namespace auth {

class default_authorizer : public authorizer {
public:
    static const sstring DEFAULT_AUTHORIZER_NAME;

    default_authorizer();
    ~default_authorizer();

    future<> init();

    future<permission_set> authorize(::shared_ptr<authenticated_user>, data_resource) const override;

    future<> grant(::shared_ptr<authenticated_user>, permission_set, data_resource, sstring) override;

    future<> revoke(::shared_ptr<authenticated_user>, permission_set, data_resource, sstring) override;

    future<std::vector<permission_details>> list(::shared_ptr<authenticated_user>, permission_set, optional<data_resource>, optional<sstring>) const override;

    future<> revoke_all(sstring) override;

    future<> revoke_all(data_resource) override;

    const resource_ids& protected_resources() override;

    future<> validate_configuration() const override;

private:
    future<> modify(::shared_ptr<authenticated_user>, permission_set, data_resource, sstring, sstring);
};

} /* namespace auth */
