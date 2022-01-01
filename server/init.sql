
create table if not exists 'users' (
       'id' integer primary key autoincrement,
       'name' varchar(20) not null unique,
       'password' varchar(20) not null, -- tak się tego nie robi ale trudno
       'publisher' bool default false
);

insert into users (name, password, publisher)
values ('publisher', '123', true);
insert into users (name, password)
values ('user1', '123');
