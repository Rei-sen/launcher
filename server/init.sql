drop table if exists 'users';
create table 'users' (
       'id' integer primary key autoincrement,
       'name' varchar(20) not null unique,
       'password' varchar(20) not null, -- tak się tego nie robi ale trudno
       'publisher' bool default false
);

insert into users (id, name, password, publisher)
values (1, 'publisher', '123', true);
insert into users (id, name, password)
values (2, 'user1', '123');
insert into users (id, name, password)
values (3, 'user2', '123');

drop table if exists 'games';
create table 'games' (
       'id' integer primary key autoincrement,
       'name' text not null,
       'description' text not null,
       'price' money not null
);

insert into 'games' (id, name, description, price)
values (1, 'bezdlc', 'gra bez dlc', 10.0);

insert into 'games' (id, name, description, price)
values (2, 'zdlc', 'gra z dlc', 5.55);

drop table if exists 'gameOwnership';
create table 'gameOwnership' (
       'userID' integer not null,
       'gameID' integer not null,
       foreign key (userID) references users(id),
       foreign key (gameID) references games(id),
       primary key (userID, gameID)
);

insert into 'gameOwnership' (userID, gameID)
values (3, 2);

drop table if exists 'news';
create table 'news' (
       'gameID' integer not null,
       'id' integer not null,
       'title' text not null,
       'content' text not null,

       foreign key (gameID) references games(id),
       primary key (gameID, id)
);

insert into 'news' (gameID, id, title, content)
values (1, 1, 'tytul', 'tresc');

drop table if exists 'dlcs';
create table 'dlcs' (
       'gameID' integer not null,
       'id' integer not null,
       'title' text not null,
       'price' money not null,

       foreign key (gameID) references games(id),
       primary key (gameID, id)
);

insert into 'dlcs' (gameID, id, title, price)
values (2, 1, 'dlc 1', 2.99);

drop table if exists 'dlcOwnership';
create table 'dlcOwnership' (
       'userID' integer not null,
       'gameID' integer not null,
       'dlcID' integer not null,
       foreign key (userID) references users(id),
       foreign key (gameID, dlcID) references dlcs(gameID, id),
       primary key (userID, gameID, dlcID)
);

insert into 'dlcOwnership' (userID, gameID, dlcID)
values (3, 2, 1);

drop table if exists 'socialMedias';
create table 'socialMedias' (
       'id' integer primary key autoincrement,
       'name' text not null,
       'address' text not null
);

insert into 'socialMedias' (name, address)
values ('abc', 'abc.def');
